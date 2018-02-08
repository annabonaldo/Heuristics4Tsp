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
} TSPMove;

class Solver
{
public:
	/** Constructor */
	Solver() {
		verbose = false; 
	}
	bool verbose; 

	std::string name() { return "TSEARCH";  }
	/**
	* evaluate a solution
	* @param sol: solution to be evaluated
	* @param TSP: TSP data
	* @return the value of the solution
	*/
	double solutionLengthValue(const TSPSolution& sol, const TSP& tsp) const {
		double total = 0.0;
		for (int i = 0; i < sol.sequence.size() - 1; ++i) {
			int from = sol.sequence[i];
			int to = sol.sequence[i + 1];
			total += tsp.cost[from][to];
		}
		return total;
	}
	/**
	* initialize a solution as a random sequence by random swaps
	* @param sol solution to be initialized
	* @return true if everything OK, false otherwise
	*/
	 bool initRnd(TSPSolution& sol) {
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

	 /**
	 * initialize a solution as previously computed solution. 
	 * @param sol solution to be initialized
	 * @return true if everything OK, false otherwise
	 */
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

	/**
	* search for a good tour by neighbourhood search
	* @param TSP TSP data
	* @param initSol initial solution
	* @param bestSol best found solution (output)
	* @return true id everything OK, false otherwise
	*/
	std::string solve(const TSP& tsp, const TSPSolution& initSol, int tabulength, int maxIter, TSPSolution& bestSol);

protected:
	static double getWallTime();

	/**
	* explore the neighbouhood
	* @param tsp TSP data
	* @param currSol center solution
	* @return (into param move) the selected move (stepest descent strategy)
	* @return the incremental cost with respect to currSol
	*/
	double       findBestNeighbor(const TSP& tsp, const TSPSolution& currSol, int currIter, TSPMove& move);
	/**
	* perform a swap move (corresponding to 2-opt)
	* @param tspSol solution to be perturbed
	* @param move move to perform
	* @return (into param tspSol) the perturbed solution
	*/
	TSPSolution&  swap(TSPSolution& tspSol, const TSPMove& move);

	int tabuLength;
	std::vector<int>  tabuList;
	bool  initTabuList(int n) {
		for (int i = 0; i < n; ++i) {
			tabuList.push_back(-tabuLength - 1);
			// at iterarion 0, no neighbor is tabu --> iteration(= 0) - tabulistInit > tabulength --> tabulistInit < tabuLength + 0
		}
		return true;
	}
	///
};
