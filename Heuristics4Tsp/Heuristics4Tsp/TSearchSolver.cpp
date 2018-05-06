#include "stdafx.h"
#include "TSearchSolver.h"
#include <iostream>
#include <string>
using namespace std;


std::string TSearchSolver::solve(const TSP& tsp, const TSPSolution& initSol,  TSPSolution& bestSol)   /// TS: new param
{
	std::string line = "";
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
			if (tsp.n < 20) currSol.print();
			//std::cout << " (" << iter << ") value " << currValue << "\t(" << solutionLengthValue(currSol, tsp) << ")";      /// TS: iter
			double aspiration = bestValue - currValue;                                                            //**// TSAC: aspired IMPROVEMENT (to improve over bestValue)
			double bestNeighValue = currValue + findBestNeighbor(tsp, currSol, iter, aspiration, move);             //**// TSAC: aspiration
																													//if ( bestNeighValue < currValue ) {                                                               /// TS: replace stopping and moving criteria
																													//  bestValue = currValue = bestNeighValue;                                                         ///
																													//  currSol = swap(currSol,move);                                                                   ///
																													//  stop = false;                                                                                   ///
																													//} else {                                                                                          ///
																													//  stop = true;                                                                                    ///
																													//}                                                                                                 ///

			if (bestNeighValue >= tsp.infinite) {                                                             // TS: stop because all neighbours are tabu
			//	std::cout << "\tmove: NO legal neighbour" << std::endl;                                           //
				stop = true;                                                                                      //
				continue;                                                                                         //
			}                                                                                                            //

			tabuList[currSol.sequence[move.from]] = iter;                                                       /// TS: update tabu list
			tabuList[currSol.sequence[move.to]] = iter;                                                       ///
			currSol = swap(currSol, move);                                                                       /// TS: always the best move
			currValue = bestNeighValue;                                                                         /// 
			if (currValue < bestValue - 0.01) {                                                                /// TS: update incumbent (not always)
				bestValue = currValue;                                                                            ///
				bestSol = currSol;                                                                                ///
                                                                          ///
			}                                                                                                   ///

			if (iter > maxIter) {                                                                             /// TS: new stopping criteria
				stop = true;                                                                                      ///
			}                                                                                                   ///
	
		}
		bestSol = currSol;                                                                                  /// TS: not always improves
  
		double endTime = getWallTime();
		string problemSize = to_string(tsp.n);
		string time = to_string(endTime - startTime);
		string solSize = to_string(solutionLengthValue(bestSol, tsp));


		line = std::string("Solution;") + solSize +
			";Problem size; " + problemSize +
			";Time; " + time;


	return getLine(solSize, problemSize, time);
}

double TSearchSolver::findBestNeighbor(const TSP& tsp, const TSPSolution& currSol, int currIter, double aspiration, TSPMove& move)
/* Determine the *move* yielding the best 2-opt neigbor solution
*/
{

	double bestCostVariation = tsp.infinite;

	for (int a = 1; a < currSol.sequence.size() - 2; a++) {
		int h = currSol.sequence[a - 1];
		int i = currSol.sequence[a];
		for (int b = a + 1; b < currSol.sequence.size() - 1; b++) {
			int j = currSol.sequence[b];
			int l = currSol.sequence[b + 1];
			//**// TSAC: to be checked after... if ( (currIter - tabuList[i] <= tabuLength) && (currIter - tabuList[j] <= tabuLength) ) continue;
			double neighCostVariation = -tsp.cost[h][i] - tsp.cost[j][l]
				+ tsp.cost[h][j] + tsp.cost[i][l];
			if ((currIter - tabuList[i] <= tabuLength) && (currIter - tabuList[j] <= tabuLength) && !(neighCostVariation < aspiration - 0.01)) {
				continue;             //**// TSAC: check if tabu and not aspiration criteria
			}
			if (neighCostVariation < bestCostVariation) {
				bestCostVariation = neighCostVariation;
				move.from = a;
				move.to = b;
			}
			if ( bestCostVariation < 0 ) return bestCostVariation;
		}
	}
	return bestCostVariation;
}






