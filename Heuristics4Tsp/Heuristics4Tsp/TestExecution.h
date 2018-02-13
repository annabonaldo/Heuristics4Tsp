#pragma once
#include "Solver.h"

class TestExecution
{
	enum DATASET {DATASET_RAND, DATASET_GRID, DATASET_SEMIGRID};

public:
	static bool RANDactive;
	static bool GRIDactive; 
	static bool SEMIGRIDactive; 
	static bool VERBOSE;
	static bool PRINT_EX_METHOD;
	static bool PRINT_IN_FILE; 
	static bool PRINT_DATASET;
	static bool PT100_PROBLEM_SIZE; 
	static void ExecuteTest(Solver& solver); 

	static void ExecuteTestOnTABU_SEARCH(); 
	static void ExecuteTestOnGREEDY_SEARCH(); 
	static void ExecuteTestOnSIM_ANNEALING(); 
	static void ExecuteTestOnStrightGREEDYLine_SEARCH(); 
	static void ExecuteTestALL_PROBLEM_SIZE(Solver& solver);
	static void ExecuteTestFIXED_PROBLEM_SIZE(Solver& solver);

	static void ExecuteTestLowPerformamcesALL_PROBLEM_SIZE(Solver& solver);
	static void ExecuteTestLowPerformamcesFIXED_PROBLEM_SIZE(Solver& solver);

	static void ExecuteTestOnTABU_SEARCHIterationNum(int lenght); 

	static void writeResults(std::string outFile);
	static void writeData(std::vector<std::string>& data, std::string outFile); 

	

	
private: 
	static std::vector < std::string> datasets;
	static std::vector<std::string> results;
	
	
	/*
	clock_t t1, t2;
	t1 = clock();
	*/
		
};

