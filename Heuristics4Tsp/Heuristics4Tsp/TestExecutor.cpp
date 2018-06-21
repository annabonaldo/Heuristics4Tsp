#include "stdafx.h"
#include "TestExecutor.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "DatasetGenerator.h"
#include "TSearchSolver.h"
#include "GreedySolver.h"
#include "SimAnnealingSolver.h"
#include "TSPViewer.h"

bool TestExecutor::VERBOSE = false;
TestExecutor::TestExecutor()
{
}

TestExecutor::~TestExecutor()
{
}

void TestExecutor::Execute(std::vector<ActiveTSPSolver> & activeAlgorithms, std::vector<Dataset::ActiveDataset> & activeDatasets)
{
	DatasetGenerator::generate(activeDatasets);

	for (std::vector<ActiveTSPSolver>::iterator algIt = activeAlgorithms.begin(); algIt != activeAlgorithms.end(); algIt++)
	{
		ActiveTSPSolver activeSolver = *algIt;
		switch (activeSolver)
		{
		case ActiveTSPSolver::Greedy:
		{
			GreedySolver solver = GreedySolver();
			ExecuteOnActiveDatasets(solver);
			break;
		}
		case ActiveTSPSolver::GreedyOptimized2opt:
		{
			GreedySolver solver = GreedySolver();
			solver.optimized = true;
			ExecuteOnActiveDatasets(solver, true);
			break;
		}

		case ActiveTSPSolver::SimAnnealing_T1e3_delta1_e1:
		{
			srand(111);
			SimAnnealingSolver solver = SimAnnealingSolver(1e3, 1e-1);
			ExecuteOnActiveDatasets(solver);
			break;
		}
		case ActiveTSPSolver::SimAnnealing_T1e3_delta5_e5:
		{
			srand(27);
			SimAnnealingSolver solver = SimAnnealingSolver(1e3, 5e-5);
			ExecuteOnActiveDatasets(solver);
			break;
		}
		case ActiveTSPSolver::SimAnnealing_T5e5_delta1_e1:
		{
			srand(4);
			SimAnnealingSolver solver = SimAnnealingSolver(5e5, 1e-1);
			ExecuteOnActiveDatasets(solver);
			break;
		}
		case ActiveTSPSolver::SimAnnealing_T5e5_delta5_e5:
		{
			srand(320);
			SimAnnealingSolver solver = SimAnnealingSolver(5e5, 5e-5);
			ExecuteOnActiveDatasets(solver);
			break;
		}

		case ActiveTSPSolver::SimAnnealing_T1e6_delta1_e1:
		{
			srand(110);
			SimAnnealingSolver solver = SimAnnealingSolver(1e6, 1e-1);
		//	ExecuteOnActiveDatasets(solver, false, false);
			/*ExecuteOnActiveDatasets(solver, true, false);*/
		
			ExecuteOnActiveDatasets(solver, false, true);
			//ExecuteOnActiveDatasets(solver, true, true);
			break;
		}

		case ActiveTSPSolver::SimAnnealing_T1e6_delta5_e5:
		{
			srand(256);
			SimAnnealingSolver solver = SimAnnealingSolver(1e6, 5e-5);
		//	ExecuteOnActiveDatasets(solver, false, false);
			/*ExecuteOnActiveDatasets(solver, true, false);*/
			ExecuteOnActiveDatasets(solver, false, true);
			//ExecuteOnActiveDatasets(solver, true, true);
			break;
		}

		case ActiveTSPSolver::TabuSearch_Static_maxIter1e5:
		{
			std::cout << "TabuSearch_Static_maxIter1e5" << std::endl;

			TSearchSolver solver;
			solver = TSearchSolver(1e2, 1e5);
			ExecuteOnActiveDatasets(solver);

			solver = TSearchSolver(1e3, 1e5);
			ExecuteOnActiveDatasets(solver);

			solver = TSearchSolver(1e4, 1e5);
			ExecuteOnActiveDatasets(solver);

			solver = TSearchSolver(1e5, 1e5);
			ExecuteOnActiveDatasets(solver);
			break;

		}
		case ActiveTSPSolver::TabuSearch_Static_maxIter1e3:
		{

			std::cout << "TabuSearch_Static_maxIter1e3" << std::endl;
			TSearchSolver solver;
			std::cout << "---------------------------  listLenght:1e2 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e2, 1e3);
			ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e3 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e3, 1e3);
			ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e4 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e4, 1e3);
			ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e5 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e5, 1e3);
			ExecuteOnActiveDatasets(solver);
			std::cout << "----------------------------------------------------- " << std::endl;
			break;
		}
		case ActiveTSPSolver::TabuSearch_Dynamic_SizeProportional:
		{
			std::cout << "TabuSearch_Dynamic_SizeProportional" << std::endl;
			ExecuteTSearchWhithSizeBasedParameters(false, true, true);
			std::cout << "----------------------------------------------------- " << std::endl;
			break;
		}

		case ActiveTSPSolver::TabuSearch_DynamicProportionalOpt:
		{
			std::cout << "TabuSearch_DynamicProportionalOpt" << std::endl;
			ExecuteTSearchWhithSizeBasedParameters(false, true, false);
			std::cout << "----------------------------------------------------- " << std::endl;
			break;
		}

		case ActiveTSPSolver::TabuSearch_Dynamic_ProportionalOptAndPrecomputeSol:
		{
			std::cout << "TabuSearch_Dynamic_ProportionalOptAndPrecomputeSol" << std::endl;
			ExecuteTSearchWhithSizeBasedParameters(true, true, true);
			std::cout << "----------------------------------------------------- " << std::endl;
			break;
		}
		case ActiveTSPSolver::TabuSearch_DynamicBase:
		{
			std::cout << "TabuSearch_DynamicBase" << std::endl;

			/*TSearchSolver solver;
			std::cout << "---------------------------  listLenght:1e2 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e2,1e3, 1e2, 1e5);

			ExecuteOnActiveDatasets(solver, true, true);
			std::cout << "---------------------------  listLenght:1e3 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e3,1e4, 1e2, 1e5);

			ExecuteOnActiveDatasets(solver, true, true);
			std::cout << "---------------------------  listLenght:1e4 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e4,1e5, 1e2, 1e5);

			ExecuteOnActiveDatasets(solver, true, true);
			std::cout << "---------------------------  listLenght:1e5 maxiter: 1e3" << std::endl;
			solver = TSearchSolver(1e5,1e6, 1e2, 1e5);

			ExecuteOnActiveDatasets(solver, true, true);
			std::cout << "----------------------------------------------------- " << std::endl;
			break; */
			TSearchSolver solver;
			std::vector<double> lists = { 1e3, 1e6, 1e8, 1e10 };
			for (int i = 0; i < lists.size(); i++)
			{
				solver = TSearchSolver(lists[i], lists[i] , (int)std::sqrt(lists[i]), 1e6);
			}
			break;

		}

		case ActiveTSPSolver::TabuSearch_Dynamic_x2_x10:
		{
			std::cout << "TabuSearch_Dynamic_x2_x10" << std::endl;
			TSearchSolver solver;
			std::cout << "---------------------------  listLenght:1e3 to 1e3 * 2 iterVarLenght: 50   maxiter: 1e5" << std::endl;
			solver = TSearchSolver(1e3, 1e3 * 2, 50, 1e5); ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e3 to 1e4 iterVarLenght: 200   maxiter: 1e5" << std::endl;
			solver = TSearchSolver(1e3, 1e4, 200, 1e5); ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e5 to 1e5 * 2 iterVarLenght: 50   maxiter: 1e5" << std::endl;
			solver = TSearchSolver(1e5, 1e5 * 2, 50, 1e5); ExecuteOnActiveDatasets(solver);
			std::cout << "---------------------------  listLenght:1e5 to 1e6 iterVarLenght: 200   maxiter: 1e5" << std::endl;
			solver = TSearchSolver(1e5, 1e6, 200, 1e5); ExecuteOnActiveDatasets(solver);

			std::cout << "----------------------------------------------------- " << std::endl;
			break;
		}


	deafult:
		{
			break;
		}
		}
	}
}
void TestExecutor::ExecuteTest(Solver & solver, Dataset & dataset, std::string  key, int problem_size, bool precompute)
{
	std::cout << "Execute Test  with solver: " << solver.name() << " -- dataset: " << dataset.name << " -- in: " << key << std::endl;
	std::string input_filename = dataset.input_files.at(key);

	TSP tspInstance; // read Problem 
	DatasetGenerator::readDataset(input_filename, tspInstance, problem_size);


	TSPSolution aSolution(tspInstance); // build initial solution 
	solver.initRnd(aSolution); // init RANDOM soultion
	TSPSolution bestSolution(tspInstance); // build obj for best solution 

	if (precompute)
	{
		GreedySolver pre_solver = GreedySolver();
		pre_solver.optimized = true;
		std::string preLine = pre_solver.solve(tspInstance, aSolution, bestSolution);
		aSolution = bestSolution;
		writeResult(dataset.output_stats, dataset.name + ";" + preLine+ "greedy precomputed; ");
	}
	solver.precomputed = precompute; 
	std::string resultline = solver.solve(tspInstance, aSolution, bestSolution);
	writeResult(dataset.output_stats, dataset.name + ";" + resultline);

	TSPViewer::drawTSP(bestSolution,
		tspInstance,
		"dataReports\\paths\\" + solver.name() + dataset.name + key,
		DatasetGenerator::datasetRadius(dataset.type, problem_size),
		problem_size); 

	if (VERBOSE)
	{
		std::cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
		std::cout << "FROM solution: ";
		std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
		std::cout << "TO   solution: ";
		std::cout << "(Lenght value : " << solver.solutionLengthValue(bestSolution, tspInstance) << ")\n";
		std::cout << "------------------------------------------" << std::endl;
	}
}

void TestExecutor::ExecuteTSearchWhithSizeBasedParameters(bool optimize, bool precompute, bool dynamicTSearch)
{

	std::vector<Dataset>::iterator dit = DatasetGenerator::datasets.begin();
	for (; dit != DatasetGenerator::datasets.end(); dit++)
	{
		TSP tspinstance;
		std::map<std::string, std::string >::iterator file_it = dit->input_files.begin();

		for (; file_it != dit->input_files.end(); file_it++)
		{

			std::string key = file_it->first;
			std::cout << "--- on Dataset: [key: " << key;
			std::cout << "] [size:" << dit->input_sizes.at(key);
			std::cout << "] [filepath: " << dit->input_files.at(key) << "]" << std::endl;
			if (dynamicTSearch)
			{
				int N = dit->input_sizes.at(key);
				std::cout << "--------------------------- Dynamic N*N, N*N * 10, N, N*N*N)" << std::endl;
				TSearchSolver solver1(N*N, N*N * 10, N, N*N*N);
				ExecuteTest(solver1, *dit, key, dit->input_sizes.at(key), precompute);
				std::cout << "--------------------------- Dynamic N*N, N*N * 100, N * 10, N*N*N)" << std::endl;
				TSearchSolver solver2(N*N, N*N * 100, N * 10, N*N*N);
				ExecuteTest(solver2, *dit, key, dit->input_sizes.at(key), precompute);
			}
			else
			{
				int N = dit->input_sizes.at(key);
				std::cout << "--------------------------- Static N*N, N*N*N)" << std::endl;
				TSearchSolver solverStatic(N*N, N*N*N);
				ExecuteTest(solverStatic, *dit, key, dit->input_sizes.at(key), precompute);

			}
		}
	}
}

void TestExecutor::ExecuteOnActiveDatasets(Solver & solver, bool optimize, bool precompute)
{
	std::cout << "Execution with Solver " << solver.name();
	std::vector<Dataset>::iterator dit = DatasetGenerator::datasets.begin();
	for (; dit != DatasetGenerator::datasets.end(); dit++)
	{
		TSP tspinstance;
		std::map<std::string, std::string >::iterator file_it = dit->input_files.begin();
		for (; file_it != dit->input_files.end(); file_it++)
		{
			std::string key = file_it->first;
			std::cout << "--- on Dataset: [key: " << key;
			std::cout << "] [size:" << dit->input_sizes.at(key);
			std::cout << "] [filepath: " << dit->input_files.at(key) << "]" << std::endl;
			if (optimize)
				solver.optimized = true; 
			ExecuteTest(solver, *dit, key, dit->input_sizes.at(key), precompute);
		}
	}
}

void TestExecutor::writeResult(std::string outfile, std::string line)
{	
	std::ofstream out(outfile, std::ios::app);

	out << line.c_str() << "\n";

	std::cout << "writeResult: " << line << std::endl;

}

const std::string TestExecutor::currentDateTime() {

	return "ven 15 06";
}

