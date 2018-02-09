#pragma once
#include "Solver.h"
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
	std::string name() override { return  "SIMANNEALING"; }
};

