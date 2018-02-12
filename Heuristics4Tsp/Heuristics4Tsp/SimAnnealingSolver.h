#pragma once
#include "Solver.h"
#include <string>
class SimAnnealingSolver :
	public Solver
{
private: 
	double T; 
	double delta; 
public:
	SimAnnealingSolver(double t, double d) : Solver(), T(t), delta(d) {}
	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol); 
	double acceptanceProbability(double currPathLenght, double neighPathLenght, double temperature); 
	std::string name() override { return  "SIMANNEALING; Temperature;"+std::to_string((int)T)+";Delta;" + std::to_string(delta)+";"; }
	std::string filename() override { return  "SIMANNT" + std::to_string((int)T) + "d" + std::to_string((int)delta);  }
};

