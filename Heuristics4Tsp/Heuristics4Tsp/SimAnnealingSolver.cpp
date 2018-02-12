#include "stdafx.h"
#include "SimAnnealingSolver.h"
#include <string>

std::string SimAnnealingSolver::solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) {
	bool stop = false;
	int  iter = 0;

	double startTime = getWallTime();
	TSPSolution currSol(initSol);
	bestSol = initSol; 
	double nextValue, currValue;
	nextValue = currValue = solutionLengthValue(currSol, tsp);
	double temperature = T;
	/*verbose = true; */
	while (temperature > 1.0) {
		// Create new neighbour tour
		TSPSolution newSol = currSol; 
		srand(time(NULL));
		// Get a random positions in the tour
		int tourPos1, tourPos2; 
		tourPos1 = tourPos2 = randomINT(0, tsp.n);
		while(tourPos1== tourPos2) tourPos2 = randomINT(0, tsp.n);

		TSPMove m(tourPos1, tourPos2); 
		if(verbose) std::cout << "move : " << m.from << " -> " << m.to << std::endl; 
		// Swap them
		this->swap(newSol, m); 

		// Get energy of solutions
		double currPathLenght = solutionLengthValue(currSol, tsp);
		double neighPathLenght = solutionLengthValue(newSol, tsp);


		// Decide if we should accept the neighbour
		double prob = acceptanceProbability(currPathLenght, neighPathLenght, T); 
		if (prob > randomDOUBLE(0.0, 1.0)) {
			currSol = newSol; 
			if(verbose) std::cout << " new solution accepted: prob = " << prob << std::endl; 
		}

		// Keep track of the best solution found
		if (solutionLengthValue(currSol, tsp) < solutionLengthValue(bestSol, tsp)) {
			bestSol = currSol;
		}

		// Cool system
		temperature *= 1 - delta;
		if (verbose) std::cout << " temperature = " << temperature << std::endl;
	}
	if (verbose) std::cout << "END EXECUTION" << std::endl; 
	double endTime = getWallTime();
	std::string problemSize = std::to_string(tsp.n);
	std::string time = std::to_string(endTime - startTime);
	std::string solSize = std::to_string(solutionLengthValue(bestSol, tsp));

	return getLine(solSize, problemSize, time);
	
}


double SimAnnealingSolver::acceptanceProbability(double currPathLenght, double neighPathLenght, double temperature) {
	if (neighPathLenght < currPathLenght) 
		return 1.5;
	// If the new solution is worse, calculate an acceptance probability
	return std::exp((currPathLenght - neighPathLenght) / temperature);
}