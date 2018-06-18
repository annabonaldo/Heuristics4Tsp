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
		GreedyOptimized2opt,

		SimAnnealing_T5e5_delta1_e1,
		SimAnnealing_T5e5_delta5_e5,
		SimAnnealing_T1e3_delta1_e1,
		SimAnnealing_T1e3_delta5_e5,
		SimAnnealing_T1e6_delta1_e1,
		SimAnnealing_T1e6_delta5_e5, 
		

		TabuSearch_Static_maxIter1e5,
		TabuSearch_Static_maxIter1e3, 
		TabuSearch_Dynamic_x2_x10, 
		TabuSearch_Dynamic_SizeProportional, 
		TabuSearch_Static_SizeProportional,
		TabuSearch_DynamicBase,
		TabuSearch_DynamicProportionalOpt,
		TabuSearch_Dynamic_ProportionalOptAndPrecomputeSol
		
	};

	TestExecutor();
	~TestExecutor();

	static void ExecuteTest(Solver & solver, Dataset  & dataset, std::string  key, int problem_size, bool precompute = false);
	static void writeResult(std::string outfile, std::string line);
	static const std::string TestExecutor::currentDateTime(); 
	static void Execute(std::vector<ActiveTSPSolver> & activeAlgorithms, std::vector<Dataset::ActiveDataset> & activeDatasets);
	static void ExecuteOnActiveDatasets(Solver & solver, bool optimize = false, bool precompute = false); 
	static void TestExecutor::ExecuteTSearchWhithSizeBasedParameters(bool optimize, bool precompute, bool dynamicTSearch); 
}; 