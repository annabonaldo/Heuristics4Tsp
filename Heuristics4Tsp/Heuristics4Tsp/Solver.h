#pragma once
#include <vector>
#include <time.h>
#include "TSPSolution.h"
#include "TSP.h"
#ifndef _WIN32
#define _WIN32
#endif
#include <Windows.h>
typedef struct move {
	int			from;
	int			to;
	move() {}
	move(int a, int b ): from(a), to(b){}
} TSPMove;

class Solver
{
public:
	
	Solver() {
		verbose = false; 
	}

	bool verbose; 
	
	virtual std::string name() = 0; 

	double solutionLengthValue(const TSPSolution& sol, const TSP& tsp) const; 
	
	bool initRnd(TSPSolution& sol); 

	bool initFormFile(TSPSolution& sol) {
		bool exit = true;
		try {
			std::ifstream in(sol.filename.c_str());
			int n;
			// read size
			in >> n;
		//	std::cout << "number of nodes n = " << n << std::endl;
			// read nodes
			sol.sequence.clear();
			sol.sequence.reserve(n);
			for (int i = 0; i < n; i++) {
				int c;
				in >> c;
				sol.sequence.at(i) = c;
			}
		}
		catch (...) {
			exit = false;
		}

		return exit;
	}

	virtual std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) = 0; 
	virtual std::string filename() = 0;
	virtual bool isLowPerformance() { return false;}
	std::vector<std::string> solValues;

protected:
	
	static double getWallTime();
	TSPSolution&  swap(TSPSolution& tspSol, const TSPMove& move);
	int randomINT(int min, int max); 
	double randomDOUBLE(double min, double max);
	std::string getLine(std::string solSize, std::string  problemSize, std::string  time)
	{
		std::string  line = std::string("Solution;") + solSize +
			";Problem size; " + problemSize +
			";Time; " + time;

		line = line + ";" + name();
	//	line = line.replace(line.begin(), line.end(), ".", ","); 
		return line;
	}


};
