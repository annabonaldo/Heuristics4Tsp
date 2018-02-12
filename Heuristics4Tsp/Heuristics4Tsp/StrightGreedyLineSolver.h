#pragma once
#include "Solver.h"
#include <string>
class StrightGreedyLineSolver :
	public Solver
{
	double k; // angle penality
	double m; // module penality
	double lineOffset; 
public:
	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol);
	StrightGreedyLineSolver(double anglepenality, double modulepenality, double offset):k(anglepenality), m(modulepenality), lineOffset(offset){}
	std::string name() override { return  "STRIGHTGREEDYLIN; Angle;"+
	 std::to_string(k)+"; Module;"+ std::to_string(m)+"; LineOffset; "+ std::to_string((int)lineOffset)+";"; }
	std::string filename() override { return "results";  };
};

