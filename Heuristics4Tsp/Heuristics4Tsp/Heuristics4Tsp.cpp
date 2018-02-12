// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <ctime>
#include "TestExecution.h"
#include <math.h>
// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	try
	{
		std::string outFile= "data\\results\\resultsStats.csv";
		
		bool GREEDY_SEARCH = false;
		bool StrightGREEDYLine_SEARCH = false;
		bool TABU_SEARCH = false;
		bool SIM_ANNAEALING = false; 
		bool TABU_SEARCH_ITERNUM = true; 
		
		if (GREEDY_SEARCH) TestExecution::ExecuteTestOnGREEDY_SEARCH(); 
		if (StrightGREEDYLine_SEARCH) TestExecution::ExecuteTestOnStrightGREEDYLine_SEARCH();
		if (TABU_SEARCH)   TestExecution::ExecuteTestOnTABU_SEARCH(); 
		if(GREEDY_SEARCH || StrightGREEDYLine_SEARCH ||TABU_SEARCH)TestExecution::writeResults(outFile);
		if (SIM_ANNAEALING) TestExecution::ExecuteTestOnSIM_ANNEALING(); 
		if (TABU_SEARCH_ITERNUM) 
		{
			std::string outFile = "data\\results\\resultsTabuITERN.txt";
			TestExecution::ExecuteTestOnTABU_SEARCHIterationNum(10000);
			TestExecution::writeResults(outFile);
		}
		std::cin.ignore();
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}

