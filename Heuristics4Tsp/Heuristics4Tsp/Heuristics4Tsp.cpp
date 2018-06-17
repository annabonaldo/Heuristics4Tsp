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
	std::vector<DatasetGenerator::ActiveDataset> activeDatasets = { 
	    DatasetGenerator::ActiveDataset::RandActive, 
		DatasetGenerator::ActiveDataset::GridActive,
		DatasetGenerator::ActiveDataset::SemigridActive,
		DatasetGenerator::ActiveDataset::ConstRand5000Active, 
		DatasetGenerator::ActiveDataset::ConstRand50Active
	}; 

	std::vector<TestExecutor::ActiveTSPSolver> activeSolvers = {
		 //TestExecutor::ActiveTSPSolver::Greedy,
		//TestExecutor::ActiveTSPSolver::SimAnnealing_T1e3_delta1_e1,
		TestExecutor::ActiveTSPSolver::SimAnnealing_T1e3_delta5_e3, 
		TestExecutor::ActiveTSPSolver::SimAnnealing_T5e5_delta1_e1, 
		TestExecutor::ActiveTSPSolver::SimAnnealing_T5e5_delta5_e3
		//TestExecutor::ActiveTSPSolver::SimAnnealing,
		//TestExecutor::ActiveTSPSolver::TabuSearch
	};

	TestExecutor::Execute(activeSolvers, activeDatasets);

	std::cin.ignore();

	//TSPViewer::visualizeTSP(aSolution, tspInstance, solver.name() + " before computing TSP", 2);
	//TSPViewer::visualizeTSP(endSolution, tspInstance, solver.name() + " TSP solution",2);
	/*try
	{
		std::string outFile= "data\\results\\resultsStats.csv";

		bool GREEDY_SEARCH = false; //ok
		bool StrightGREEDYLine_SEARCH = false; //no
		bool TABU_SEARCH = false;
		bool SIM_ANNAEALING = false;
		bool TABU_SEARCH_ITERNUM = true;


		//  datasets
		TestExecution::RANDactive = true;
		TestExecution::GRIDactive = true;
		TestExecution::SEMIGRIDactive = false;
		TestExecution::PT100_PROBLEM_SIZE = true;

		// debugging
		TestExecution::VERBOSE = true;
		TestExecution::PRINT_IN_FILE = false;
		TestExecution::PRINT_EX_METHOD = true;
		TestExecution::PRINT_DATASET = false;


		if (GREEDY_SEARCH) {
			std::string outFile = "data\\results\\resultsGreedy.txt";
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
			TestExecution::writeResults(outFile);
		}
		if (TABU_SEARCH_ITERNUM)
		{
			std::string outFile = "data\\results\\resultsTABUonVarNUM.txt";
			TestExecution::ExecuteTestOnTABU_SEARCHIterationNum(10000);
			TestExecution::ExecuteTestOnTABU_SEARCHIterationNum(10000000);
			TestExecution::writeResults(outFile);
		}
		std::cout << "END main EXECUTION" << std::endl;
		std::cin.ignore();
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}*/
	return 0;
}

