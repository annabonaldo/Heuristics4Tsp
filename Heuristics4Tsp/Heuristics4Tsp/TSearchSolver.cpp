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
		int notUpdatingIter = 0; 

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
			++iter;  
			increaseTSLenghtIfNecessary(notUpdatingIter); 
			//if (tsp.n < 20) currSol.print();
		
			double aspiration = bestValue - currValue;                                                            
			double bestNeighValue = currValue + findBestNeighbor(tsp, currSol, iter, aspiration, move);             
																													                                                       																													                                                                                               
			if (bestNeighValue >= tsp.infinite) {                                                             				
				notUpdatingIter++;
				continue;
			}
			else
			{
				tabuList[currSol.sequence[move.from]] = iter;
				tabuList[currSol.sequence[move.to]] = iter;
				currSol = swap(currSol, move);
				currValue = bestNeighValue;

				if (currValue < bestValue - 0.01) {
					bestValue = currValue;
					bestSol = currSol;
				
					restoreTSLenghtIfNecessary(notUpdatingIter); 
				}
				else
					notUpdatingIter++; 

				if (iter > maxIter) { stop = true;}
			}																										     
		}		

		bestSol = currSol;                                                                                   
  
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

void TSearchSolver::increaseTSLenghtIfNecessary(int notUpdatingIter)
{
	if (isDynamicTabuLenght() &&
	   (notUpdatingIter >= this->nIterChangeTabuLenght))
			tabuLength = maxTabuLenght; 
}

void TSearchSolver::restoreTSLenghtIfNecessary(int & notUpdatingIter)
{
	if (isDynamicTabuLenght() &&		
	   (notUpdatingIter >= this->nIterChangeTabuLenght))
	{
		tabuLength = minTabuLenght;
		notUpdatingIter = 0; 
	}
}




