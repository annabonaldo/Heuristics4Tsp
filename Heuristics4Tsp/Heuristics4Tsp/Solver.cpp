#include "stdafx.h"
#include "Solver.h"
#include <iostream>
#include <string>
#include <set>
#include <opencv2\opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

double Solver::getWallTime()
{
	LARGE_INTEGER time, freq;
	if (!QueryPerformanceFrequency(&freq)) {
		//  Handle error
		return 0;
	}
	if (!QueryPerformanceCounter(&time)) {
		//  Handle error
		return 0;
	}
	return (double)time.QuadPart / freq.QuadPart;
}

void Solver::optimize2opt(const TSP& tsp, TSPSolution& bestSol, int maxSwap, int iterationLimit )
{
	if (iterationLimit == 0)
		iterationLimit = tsp.n*tsp.n;

	TSPSolution tmpSol(bestSol);
	
	bool execute = (maxSwap > 0) && (iterationLimit > 0); 
	
	while (execute)
	{
		execute = (maxSwap > 0) && (iterationLimit > 0);
		for (int i = 0; i < bestSol.sequence.size() - 1 && execute; i++)
		{
			TSP::Point  segment_iStart = tsp.nodes[i];
			TSP::Point  segment_iEnd = tsp.nodes[i + 1];
			for (int j = i + 2; j < bestSol.sequence.size() && execute; j++)
			{
				TSP::Point  segment_jStart = tsp.nodes[j];
				TSP::Point  segment_jEnd = tsp.nodes[j + 1];
				if (segmentsIntersects(segment_iStart, segment_iEnd, segment_jStart, segment_jEnd))				{					TSPMove move(i, j + 1);					swap(tmpSol, move);					if (this->solutionLengthValue(tmpSol, tsp) < this->solutionLengthValue(bestSol, tsp))						bestSol = tmpSol;					else						tmpSol = bestSol;					maxSwap--;				}				iterationLimit--;			}		}
	}
}

TSPSolution& Solver::swap(TSPSolution& tspSol, const TSPMove& move)
{
	TSPSolution tmpSol(tspSol);
	if (move.from < tmpSol.sequence.size() && move.to < tmpSol.sequence.size())
	{
		for (int i = move.from; i <= move.to; ++i) {
			tspSol.sequence[i] = tmpSol.sequence[move.to - (i - move.from)];
		}
	}
	else
	{
		std::cout << "from " << move.from << " to " << move.to << " totalsize " << tmpSol.sequence.size() << std::endl; 
	}
	return tspSol;
}

double Solver::solutionLengthValue(const TSPSolution& sol, const TSP& tsp) const {
	double total = 0.0;
	std::set<int> repeat = std::set<int>(); 
//	std::cout << "sequence size " << sol.sequence.size() << std::endl; 

	for (int i = 0; i < sol.sequence.size() - 1; ++i) {
		int from = sol.sequence[i];
		if (repeat.find(from) == repeat.end())
			repeat.insert(from);
		else 
		 if(from != 0)
			 cerr << "ERROR repeated node!! Node repeated: " << from <<std::endl;
		int to = sol.sequence[i + 1];
	//	std::cout << "step " << from << " - " <<to << " : " << tsp.cost[from][to] << std::endl; 
		total += tsp.cost[from][to];
	}

	return total;
}

bool Solver::initRnd(TSPSolution& sol) {
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

int Solver::randomINT(int min, int max) //range : [min, max)
{
	//srand(time()); //seeding for the first time only!
	return min + (rand() % ((max + 1) - min));
}

double Solver::randomDOUBLE(double min, double max) //range : [min, max)
{
	
	srand(rand()); //seeding for the first time only
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}

double Solver::randProb() //range : [0, 1)
{
	return (double)rand() / (RAND_MAX + 1.0);
}

bool Solver::segmentsIntersects(const TSP::Point & o1_in, const TSP::Point& p1_in, const TSP::Point& o2_in,const TSP::Point &p2_in)
{
	cv::Point2f o1 = cv::Point2f(o1_in.x, o1_in.y);
	cv::Point2f p1 = cv::Point2f(p1_in.x, p1_in.y);
	cv::Point2f o2 = cv::Point2f(o2_in.x, o2_in.y);
	cv::Point2f p2 = cv::Point2f(p2_in.x, p2_in.y);
	
	cv::Point2f x  = o2 - o1;
	cv::Point2f d1 = p1 - o1;
	cv::Point2f d2 = p2 - o2;
	

	float cross = d1.x*d2.y - d1.y*d2.x;
	if (std::fabs(cross) < 1e-8)
		return false;

	std::vector<cv::Point2f> veritices; 
	veritices.push_back(o1); 
	veritices.push_back(o2); 
	veritices.push_back(p1); 
	veritices.push_back(p2); 
	

	double t1 = (x.x * d2.y - x.y * d2.x) / cross;
	cv::Point2f r = o1 + d1 * t1;
	double is_inside = cv::pointPolygonTest(veritices,r, false);

	return (is_inside > 1e-6);
}

