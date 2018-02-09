#pragma once
#include "Solver.h"
class RandGreedySolver :
	public Solver
{
public:
	RandGreedySolver(): Solver() {}
	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol); 
};

