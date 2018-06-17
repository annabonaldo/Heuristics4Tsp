#include "stdafx.h"
#include "SimAnnealingSolver.h"
#include <string>

std::string SimAnnealingSolver::solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) {
	

	int  iter = 0;
	bool timer_stop = false; 
	double max_time_in_seconds = 1800.0; 
	double startTime = getWallTime();
	TSPSolution currSol(initSol);
	bestSol = initSol; 
	double nextValue, currValue;
	nextValue = currValue = solutionLengthValue(currSol, tsp);
	double temperature = T;
	/*verbose = true; */
	while (temperature > 1.0 && !timer_stop) {
		if (getWallTime() - startTime > max_time_in_seconds)
			timer_stop = true; 
		// Create new neighbour tour
		TSPSolution newSol = currSol; 
		srand(time(NULL));
		// Get a random positions in the tour
		int tourPos1, tourPos2;
		tourPos1 = position % tsp.n;	
		tourPos2 = (position + rand()) % tsp.n;
		if (tourPos1 < 0) tourPos1 = (-1 * tourPos1) % tsp.n; 
		if (tourPos2 < 0) tourPos2 = (-1 * tourPos2) % tsp.n;
		position+= rand(); 
		TSPMove m(tourPos1, tourPos2); 
		if(verbose) std::cout << "move : " << m.from << " -> " << m.to << std::endl; 
		// Swap them
		this->swap(newSol, m); 
		
		// Get energy of solutions
		double bestPathLenght = solutionLengthValue(bestSol, tsp);
		double neighPathLenght = solutionLengthValue(newSol, tsp);


		// Decide if we should accept the neighbour
		double prob = acceptanceProbability(bestPathLenght, neighPathLenght, T);
		if (prob > randProb()) {
			currSol = newSol; 
			//if(verbose) std::cout << " new accepted: prob = " << prob <<" L ="<< solutionLengthValue(currSol, tsp)<<std::endl;
		}

		// Keep track of the best solution found
		if ((solutionLengthValue(currSol, tsp)- solutionLengthValue(bestSol, tsp))<1e-6) {
			bestSol = currSol;
			double newBestValue = solutionLengthValue(bestSol, tsp); 
			// std::cout << " ------------------------- improved L = " << newBestValue << std::endl;
			solValues.push_back(std::to_string(solutionLengthValue(bestSol, tsp))+"; ");
		}

		// Cool system
		temperature *= 1 - delta;
	//	if (verbose) std::cout << " temperature = " << temperature << std::endl;
	}
	
	double endTime = getWallTime();
	std::string problemSize = std::to_string(tsp.n);
	std::string time = std::to_string(endTime - startTime);
	std::string solSize = std::to_string(solutionLengthValue(bestSol, tsp));

	return getLine(solSize, problemSize, time, timer_stop);
	
}


double SimAnnealingSolver::acceptanceProbability(double bestPathLenght, double neighPathLenght, double temperature) {
	if ((neighPathLenght- bestPathLenght) < 0.01)
		return 1.5;
	// If the new solution is worse, calculate an acceptance probability
	return std::exp(-1*(neighPathLenght - bestPathLenght) / (temperature));
}