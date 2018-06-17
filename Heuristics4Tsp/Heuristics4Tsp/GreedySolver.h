#pragma once
#include "Solver.h"
class GreedySolver :
	public Solver
{
public:
	std::string name() override 
	{ 
		return  "GREEDY"+ moreFeatures();
	}
	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) override;
	
	std::string filename() override { return "results"; };
	
};

