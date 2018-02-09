#pragma once
#include "Solver.h"
class GreedySolver :
	public Solver
{
public:
	std::string name() override  { return  "GREEDY"; }
	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) override;
};

