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
		bool SIM_ANNAEALING = true; 
		bool TABU_SEARCH_ITERNUM = false; 


		//  datasets
		TestExecution::RANDactive = true;
		TestExecution::GRIDactive = true;
		TestExecution::SEMIGRIDactive = true;
		TestExecution::PT100_PROBLEM_SIZE = true;

		// debugging 
		TestExecution::VERBOSE = false;
		TestExecution::PRINT_IN_FILE = false;
		TestExecution::PRINT_EX_METHOD = false;
		TestExecution::PRINT_DATASET = false;

		
		if (GREEDY_SEARCH) {
			std::string outFile = "data\\results\\resultsGreedyLine.txt";
			TestExecution::ExecuteTestOnGREEDY_SEARCH();
			TestExecution::writeResults(outFile);
		}
		if (StrightGREEDYLine_SEARCH) {
			std::string outFile = "data\\results\\resultsGreedyLine.txt"; 
			TestExecution::ExecuteTestOnStrightGREEDYLine_SEARCH();
			TestExecution::writeResults(outFile);
		}
		if (TABU_SEARCH) {
			std::string outFile = "data\\results\\resultsTABU.txt";
			TestExecution::ExecuteTestOnTABU_SEARCH();
			TestExecution::writeResults(outFile);
		}
		if (SIM_ANNAEALING) {
			std::string outFile = "data\\results\\resultsSIMANNAEALING.txt";
			TestExecution::ExecuteTestOnSIM_ANNEALING();
		}
		if (TABU_SEARCH_ITERNUM) 
		{
			std::string outFile = "data\\results\\resultsTABUonVarNUM.txt";
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

