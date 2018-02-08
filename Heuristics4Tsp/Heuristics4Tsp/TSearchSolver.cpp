#include "stdafx.h"
#include "TSearchSolver.h"
#include <iostream>
#include <string>
using namespace std;


std::string TSearchSolver::solve(const TSP& tsp, const TSPSolution& initSol,  TSPSolution& bestSol)   /// TS: new param
{
	std::string line = "";
	try
	{
		bool stop = false;
		int  iter = 0;

		///Tabu Search
		tabuList.reserve(tsp.n);
		initTabuList(tsp.n);
		///
		double startTime = getWallTime();
		TSPSolution currSol(initSol);
		double bestValue, currValue;
		bestValue = currValue = solutionLengthValue(currSol, tsp);
		TSPMove move;
		while (!stop) {
			++iter;                                                                                             /// TS: iter not only for displaying
			if (verbose && tsp.n < 20) currSol.print();
			if (verbose) std::cout << " (" << iter << ") value " << currValue << "\t(" << solutionLengthValue(currSol, tsp) << ")";      /// TS: iter

			double bestNeighValue = currValue + findBestNeighbor(tsp, currSol, iter, move);                        /// TS: iter
																												   //if ( bestNeighValue < currValue ) {                                                               /// TS: replace stopping and moving criteria
																												   //  bestValue = currValue = bestNeighValue;                                                         ///
																												   //  currSol = swap(currSol,move);                                                                   ///
																												   //  stop = false;                                                                                   ///
																												   //} else {                                                                                          ///
																												   //  stop = true;                                                                                    ///
																												   //}                                                                                                 ///

			if (bestNeighValue >= tsp.infinite) {                                                             // TS: stop because all neighbours are tabu
				if (verbose) std::cout << "\tmove: NO legal neighbour" << std::endl;                                           //
				stop = true;                                                                                      //
				continue;                                                                                         //
			}                                                                                                   //

			if (verbose) std::cout << "\tmove: " << move.from << " , " << move.to;

			tabuList[currSol.sequence[move.from]] = iter;                                                       /// TS: update tabu list
			tabuList[currSol.sequence[move.to]] = iter;                                                       ///
			currSol = swap(currSol, move);                                                                       /// TS: always the best move
			currValue = bestNeighValue;                                                                         /// 
			if (currValue < bestValue - 0.01) {                                                               /// TS: update incumbent (if better -with tolerance- solution found)
				bestValue = currValue;                                                                            ///
				bestSol = currSol;                                                                                ///
				if (verbose) std::cout << "\t***";                                                                             ///
			}                                                                                                   /// 

			if (iter > maxIter) {                                                                             /// TS: new stopping criteria
				stop = true;                                                                                      ///
			}                                                                                                   ///
			if (verbose) std::cout << std::endl;
		}
		double endTime = getWallTime();
		string problemSize = to_string(tsp.n);
		string time = to_string(endTime - startTime);
		string solSize = to_string(solutionLengthValue(currSol, tsp));


		line = std::string("Solution;") + solSize +
			";Problem size; " + problemSize +
			";Time; " + time;
		//bestSol = currSol;                                                                                  /// TS: not always the neighbor improves over 
		///     the best available (incumbent) solution 
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
		return "error;";
	}

	return line;
}

double TSearchSolver::findBestNeighbor(const TSP& tsp, const TSPSolution& currSol, int currIter, TSPMove& move)
/* Determine the *move* yielding the best 2-opt neigbor solution
*/
{
	double bestCostVariation = tsp.infinite;

	// intial and final position are fixed (initial/final node remains 0)
	for (int a = 1; a < currSol.sequence.size() - 2; a++) {
		int h = currSol.sequence[a - 1];
		int i = currSol.sequence[a];
		for (int b = a + 1; b < currSol.sequence.size() - 1; b++) {
			int j = currSol.sequence[b];
			int l = currSol.sequence[b + 1];
			if ((currIter - tabuList[i] <= tabuLength) && (currIter - tabuList[j] <= tabuLength)) continue; /// TS: tabu check (just one among many ways of doing it...)
			double neighCostVariation = -tsp.cost[h][i] - tsp.cost[j][l]
				+ tsp.cost[h][j] + tsp.cost[i][l];
			if (neighCostVariation < bestCostVariation) {
				bestCostVariation = neighCostVariation;
				move.from = a;
				move.to = b;
			}
		}
	}
	return bestCostVariation;
	return bestCostVariation;
}






