#pragma once
#include "Solver.h"
#include "Dataset.h"
class TestExecutor
{
public:
	static bool VERBOSE; 
	TestExecutor();
	~TestExecutor();

	void ExecuteTest(Solver & solver, Dataset dataset, std::string  key, int problem_size); 
	void writeResult(std::string outfile, std::string line);
	static const std::string TestExecutor::currentDateTime(); 
}; 