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

void TestExecutor::Execute(std::vector<ActiveTSPSolver> & activeAlgorithms, std::vector<DatasetGenerator::ActiveDataset> & activeDatasets)
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
		case ActiveTSPSolver::TabuSearch: {
			TSearchSolver solver = TSearchSolver(1000, 1000);
			ExecuteOnActiveDatasets(solver);
			break;
		}

		case ActiveTSPSolver::SimAnnealing:
		{
			SimAnnealingSolver solver = SimAnnealingSolver(1000, 1000);
			ExecuteOnActiveDatasets(solver);
			break;
		}
		deafult: 
			break; 
		}
		
	}
}

void TestExecutor::ExecuteTest(Solver & solver, Dataset dataset, std::string  key, int problem_size)
{

	
	std::string input_filename = dataset.input_files.at(key); 

	TSP tspInstance; // read Problem 
	DatasetGenerator::readDataset(input_filename, tspInstance, problem_size); 
	tspInstance.printCosts(); 
//	tspInstance.read(input_filename.c_str(), problem_size);

	TSPSolution aSolution(tspInstance); // build initial solution 
	solver.initRnd(aSolution); // init RANDOM soultion
	TSPSolution bestSolution(tspInstance); // build obj for best solution 

	writeResult(dataset.output_stats , dataset.name+ ";" + solver.solve(tspInstance, aSolution, bestSolution));

	//results.push_back(*dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS

	TSPViewer::visualizeTSP(aSolution, tspInstance, solver.name() + " before computing TSP", 1);
    //TSPViewer::visualizeTSP(bestSolution, tspInstance, solver.name() + " TSP solution", getViewerScaleFactor(*dataset));
	
	if (VERBOSE) {

		std::cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
		std::cout << "FROM solution: ";

		std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
		std::cout << "TO   solution: ";
		std::cout << "(Lenght value : " << solver.solutionLengthValue(bestSolution, tspInstance) << ")\n";
		std::cout << "------------------------------------------" << std::endl;

	}
}

void TestExecutor::ExecuteOnActiveDatasets(Solver & solver)
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
			std::cout << "dataset key " << key << std::endl;
			std::cout << "dataset size "<<dit->input_sizes.at(key) << std::endl; 
			std::cout << "dataset filepath " << dit->input_files.at(key) << std::endl;
			ExecuteTest(solver, *dit, key, dit->input_sizes.at(key));
		}
	}
}

void TestExecutor::writeResult(std::string outfile, std ::string line)
{
	std::ofstream out(outfile, std::ios::app);
	out << currentDateTime().c_str() << " ;"; 
	out << line.c_str() <<"\n";

	std::cout << "writeResult: "<<line << std::endl;

}

const std::string TestExecutor::currentDateTime() {
	

	return "ven 14 06" ;
}

