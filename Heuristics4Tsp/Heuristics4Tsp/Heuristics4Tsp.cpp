// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <ctime>
#include "TestExecution.h"
#include "TSearchSolver.h"
#include "GreedySolver.h"
#include "SimAnnealingSolver.h"
#include "StrightGreedyLineSolver.h"
#include <math.h>
// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	try
	{
		bool GREEDY_SEARCH = false; 
		bool StrightGREEDYLine_SEARCH = true;
		bool TABU_SEARCH = false;
		bool SIM_ANNAEALING = false; 
		
		if (GREEDY_SEARCH)
		{
			GreedySolver solver = GreedySolver();
			TestExecution::ExecuteTest(solver);
		}
		if (TABU_SEARCH)
		{
			for (int iter = 10; iter <= 100; iter+=10)
			{
				for (int length = 10; length <= 100; length+=10)
				{
					TSearchSolver solver = TSearchSolver(length, iter);
					TestExecution::ExecuteTest(solver);
				}
			}
		
		}

		if (SIM_ANNAEALING)
		{
		//	for (int iter = 10; iter <= 100; iter += 10)
		//	{
		//		for (int length = 10; length <= 100; length += 10)
		//		{
					double temperature = 100.0;
					double delta = 0.3;
					SimAnnealingSolver solver = SimAnnealingSolver(temperature, delta);
					TestExecution::ExecuteTest(solver);
		//		}
		//	}

		}


		if (StrightGREEDYLine_SEARCH)
		{
			//	for (int iter = 10; iter <= 100; iter += 10)
			//	{
			//		for (int length = 10; length <= 100; length += 10)
			//		{
			double offset = 0; 
			double k = 100.0;
			//180 : pi  = k : x
			// x = (pi*k) / 180.0
			using namespace std; 
			double pi = atan(1) * 4;
			k = (pi*k) / 180.0; 
			double m = 0;
			StrightGreedyLineSolver solver = StrightGreedyLineSolver(k, m, offset);
			TestExecution::ExecuteTest(solver);
			//		}
			//	}

		}


		std::cin.ignore();
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}

