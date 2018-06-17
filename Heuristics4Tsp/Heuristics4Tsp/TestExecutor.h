#pragma once
#include "Solver.h"
#include "Dataset.h"
#include "DatasetGenerator.h"
class TestExecutor
{
public:
	static bool VERBOSE; 

	enum ActiveTSPSolver {
		Greedy,
		SimAnnealing_T5e5_delta1_e1,
	    SimAnnealing_T5e5_delta5_e3,
		SimAnnealing_T1e3_delta1_e1,
		SimAnnealing_T1e3_delta5_e3,
		TabuSearch
	};

	TestExecutor();
	~TestExecutor();

	static void ExecuteTest(Solver & solver, Dataset  & dataset, std::string  key, int problem_size); 
	static void writeResult(std::string outfile, std::string line);
	static const std::string TestExecutor::currentDateTime(); 
	static void Execute(std::vector<ActiveTSPSolver> & activeAlgorithms, std::vector<DatasetGenerator::ActiveDataset> & activeDatasets);
	static void ExecuteOnActiveDatasets(Solver & solver); 
}; 