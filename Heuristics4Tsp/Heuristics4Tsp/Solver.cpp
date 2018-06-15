#include "stdafx.h"
#include "Solver.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

double Solver::getWallTime()
{
	LARGE_INTEGER time, freq;
	if (!QueryPerformanceFrequency(&freq)) {
		//  Handle error
		return 0;
	}
	if (!QueryPerformanceCounter(&time)) {
		//  Handle error
		return 0;
	}
	return (double)time.QuadPart / freq.QuadPart;
}

void optimize2opt(const TSP& tsp, TSPSolution& bestSol)
{
	//double minchange = 0;

	TSPSolution tspSol(bestSol);

	//for (int i = 0; i < bestSol.sequence.size()-1; i++) {
	//	for (int j = i + 1; j < bestSol.sequence.size(); j ++) {
	//		TSPMove m1 = TSPMove(bestSol.sequence[i], bestSol.sequence[i+1]);
	//		TSPMove m2 = TSPMove(bestSol.sequence[j], bestSol.sequence[j + 1]);

	//		double change; 
	//		change = tsp.distance(m1.from, m1.to) + tsp.distance(m2.from, m2.to)
	//			- tsp.distance(m1.from, m2.from) - tsp.distance(m1.to, m2.to); 
	//		if (change > 0.01)	//		{
	//			tspSol.sequence[m1.from] = m2.to; 

	//		for (int k = m1.from+1;  <= move.to; ++k) {
	//				tspSol.sequence[k] = tmpSol.sequence[move.to - (k - move.from)];
	//			}	//		}	//			 	//	}	//}
}

TSPSolution& Solver::swap(TSPSolution& tspSol, const TSPMove& move)
{
	TSPSolution tmpSol(tspSol);
	for (int i = move.from; i <= move.to; ++i) {
		tspSol.sequence[i] = tmpSol.sequence[move.to - (i - move.from)];
	}
	return tspSol;
}

double Solver::solutionLengthValue(const TSPSolution& sol, const TSP& tsp) const {
	double total = 0.0;
	std::set<int> repeat = std::set<int>(); 
//	std::cout << "sequence size " << sol.sequence.size() << std::endl; 

	for (int i = 0; i < sol.sequence.size() - 1; ++i) {
		int from = sol.sequence[i];
		if (repeat.find(from) == repeat.end())
			repeat.insert(from);
		else
			cerr << "ERROR repeated node!! Node repeated: " << from <<std::endl;
		int to = sol.sequence[i + 1];
	//	std::cout << "step " << from << " - " <<to << " : " << tsp.cost[from][to] << std::endl; 
		total += tsp.cost[from][to];
	}

	return total;
}

bool Solver::initRnd(TSPSolution& sol) {
	srand(time(NULL));
	for (int i = 1; i < sol.sequence.size(); ++i) {
		// intial and final position are fixed (initial/final node remains 0)
		int idx1 = rand() % (sol.sequence.size() - 2) + 1;
		int idx2 = rand() % (sol.sequence.size() - 2) + 1;
		int tmp = sol.sequence[idx1];
		sol.sequence[idx1] = sol.sequence[idx2];
		sol.sequence[idx2] = tmp;
	}
	//		std::cout << "### "; sol.print(); std::cout << " ###" << std::endl;
	return true;
}

int Solver::randomINT(int min, int max) //range : [min, max)
{
	//srand(time()); //seeding for the first time only!
	return min + (rand() % ((max + 1) - min));
}

double Solver::randomDOUBLE(double min, double max) //range : [min, max)
{
	
	srand(rand()); //seeding for the first time only
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}

double Solver::randProb() //range : [0, 1)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

