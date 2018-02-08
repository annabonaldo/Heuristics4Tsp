#pragma once
#include "Solver.h"

class TestExecution
{
	enum DATASET {DATASET_RAND, DATASET_GRID, DATASET_SEMIGRID};

public:
	static bool RANDactive;
	static bool GRIDactive; 
	//static bool SEMIGRIDactive; 

	static std::string  testSetup; 
	static void ExecuteTest(Solver solver); 
	
private: 

	static void   settingsSetup();
	//static std::vector<DATASET> activeDatasets; 
	static std::string datasetID(DATASET set) 
	{
		switch (set)
		{
		case TestExecution::DATASET_RAND:
			return "RAND";
			break;
		case TestExecution::DATASET_GRID:
			return "GRID";
			break;
		case TestExecution::DATASET_SEMIGRID:
			return "SEMIGRID";
			break;
		default:
			break;
		}
       return "ERROR";
	}

	static void writeResults(std::vector<std::string> results, std::string outFile);

	/*
	clock_t t1, t2;
	t1 = clock();
	*/
		
};

