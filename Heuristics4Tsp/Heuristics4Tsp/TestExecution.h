#pragma once
#include "Solver.h"

class TestExecution
{
	enum DATASET {DATASET_RAND, DATASET_GRID, DATASET_SEMIGRID};

public:
	static bool RANDactive;
	static bool GRIDactive; 
	static bool SEMIGRIDactive; 

	static std::string  testSetup; 
	static void ExecuteTest(Solver solver); 
	
private: 
	static std::vector < std::string> datasets;
	static void writeResults(std::vector<std::string> results, std::string outFile);

	/*
	clock_t t1, t2;
	t1 = clock();
	*/
		
};

