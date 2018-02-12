#include "stdafx.h"
#include "Solver.h"
#include <iostream>
#include <string>
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
	for (int i = 0; i < sol.sequence.size() - 1; ++i) {
		int from = sol.sequence[i];
		int to = sol.sequence[i + 1];
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
	srand(time(NULL)); //seeding for the first time only!
	return min + rand() % ((max + 1) - min);
}

double Solver::randomDOUBLE(double min, double max) //range : [min, max)
{
	srand(time(NULL)); //seeding for the first time only
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}


