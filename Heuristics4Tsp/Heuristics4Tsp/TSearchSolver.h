#pragma once
#include "Solver.h"
class TSearchSolver :
	public Solver
{
public:
	/** Constructor */
	TSearchSolver(): Solver() {} 
	
	TSearchSolver(int lenght, int iter ): Solver() {
		tabuLength = lenght;
		maxIter = iter; 
	}	

	std::string name() { return "TSEARCH"; }

	std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol);

protected:
	
	double       findBestNeighbor(const TSP& tsp, const TSPSolution& currSol, int currIter, TSPMove& move);
	int maxIter;
	int tabuLength;
	std::vector<int>  tabuList;
	bool  initTabuList(int n) {
		for (int i = 0; i < n; ++i) {
			tabuList.push_back(-tabuLength - 1);
			// at iterarion 0, no neighbor is tabu --> iteration(= 0) - tabulistInit > tabulength --> tabulistInit < tabuLength + 0
		}
		return true;
	}
};

