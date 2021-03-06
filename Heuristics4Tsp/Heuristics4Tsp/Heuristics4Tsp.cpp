// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <ctime>
#include <iostream>
#include <opencv2\opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "TSPViewer.h"
#include "TestExecutor.h"
#include "DatasetGenerator.h"
// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	std::vector<Dataset::ActiveDataset> activeDatasets = {
		Dataset::ActiveDataset::RandActive,
		Dataset::ActiveDataset::GridActive,
	//	Dataset::ActiveDataset::SemigridActive,
	//	Dataset::ActiveDataset::ConstRand5000Active,
	//	Dataset::ActiveDataset::ConstRand50Active
	};

	std::vector<TestExecutor::ActiveTSPSolver> activeSolvers = {
		//	 TestExecutor::ActiveTSPSolver::Greedy,
			// TestExecutor::ActiveTSPSolver::GreedyOptimized2opt,

		//     TestExecutor::ActiveTSPSolver::TabuSearch_Static_maxIter1e3,
		//	 TestExecutor::ActiveTSPSolver::TabuSearch_Static_maxIter1e5,
			// TestExecutor::ActiveTSPSolver::TabuSearch_Static_SizeProportional,
			//
			// TestExecutor::ActiveTSPSolver::TabuSearch_Dynamic_SizeProportional,
			 TestExecutor::ActiveTSPSolver::TabuSearch_Dynamic_x2_x10, 
			// TestExecutor::ActiveTSPSolver::TabuSearch_DynamicProportionalOpt, 
			// TestExecutor::ActiveTSPSolver::TabuSearch_Dynamic_ProportionalOptAndPrecomputeSol
			 TestExecutor::ActiveTSPSolver::TabuSearch_DynamicBase,

			 //	TestExecutor::ActiveTSPSolver::SimAnnealing_T1e3_delta1_e1,
			 //	TestExecutor::ActiveTSPSolver::SimAnnealing_T1e3_delta5_e3, 
			 //	TestExecutor::ActiveTSPSolver::SimAnnealing_T5e5_delta1_e1, 
			 //	TestExecutor::ActiveTSPSolver::SimAnnealing_T5e5_delta5_e3

			// TestExecutor::ActiveTSPSolver::SimAnnealing_T1e6_delta5_e5,
			// TestExecutor::ActiveTSPSolver::SimAnnealing_T1e6_delta1_e1

	};

	TestExecutor::Execute(activeSolvers, activeDatasets);
	std::cout << "end execution " << std::endl; 
	std::cin.ignore(); return 0;
}

