#include "stdafx.h"
#include "RandGreedySolver.h"
#include <string>
#include <set>
using namespace std;


std::string RandGreedySolver::solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol)
{

	std::string line = "";
	double startTime = getWallTime();
	std::set<int> freeNodes;
	for (int i = 0; i < tsp.n; i++)
		freeNodes.insert(i);  // no node in the path at the beginning

	int step = 0;
	int curNode = *freeNodes.begin();

	while ((!freeNodes.empty()) && (step >= tsp.n))
	{
		if (freeNodes.find(curNode) != freeNodes.end())
		{
			freeNodes.erase(curNode);  // remove current node from nextNodesList
									   // iterate over all possibile newx step 
			std::set<int>::iterator next = freeNodes.begin(); // first step 
			double mindistance = tsp.distance(step, *next);
			int nextIndex = *next;
			//choose node at mininum distance
			for (; next != freeNodes.end(); next++)
			{
				double distance = tsp.distance(step, *next);

				if (distance < mindistance - 0.01)
				{
					mindistance = distance;
					nextIndex = *next;
				}
			}

			// save step 
			step++;
			if (step < tsp.n)
				bestSol.sequence.at(step) = nextIndex;
			curNode = nextIndex;
		}
		else
			bestSol.sequence[tsp.n] = curNode;


	}

	double endTime = getWallTime();
	string problemSize = to_string(tsp.n);
	string time = to_string(endTime - startTime);
	string solSize = to_string(solutionLengthValue(bestSol, tsp));


	return getLine(solSize, problemSize, time);
}