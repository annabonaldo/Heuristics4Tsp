#include "stdafx.h"
#include "TestExecutor.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

bool TestExecutor::VERBOSE = false; 
TestExecutor::TestExecutor()
{
}


TestExecutor::~TestExecutor()
{
}

void TestExecutor::ExecuteTest(Solver & solver, Dataset dataset,std::string  key, int problem_size)
{
	
	std::string input_filename = dataset.input_files.at(key); 

	TSP tspInstance; // read Problem 
	tspInstance.read(input_filename.c_str(), problem_size);

	TSPSolution aSolution(tspInstance); // build initial solution 
	solver.initRnd(aSolution); // init RANDOM soultion
	TSPSolution bestSolution(tspInstance); // build obj for best solution 

	writeResult(dataset.output_stats , dataset.name+ ";" + solver.solve(tspInstance, aSolution, bestSolution));

	//results.push_back(*dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS

	//TSPViewer::visualizeTSP(aSolution, tspInstance, solver.name() + " before computing TSP", getViewerScaleFactor(*dataset));
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

void TestExecutor::writeResult(std::string outfile, std ::string line)
{
	std::ofstream out(outfile, std::ios::app);
	out << currentDateTime().c_str() << " ;"; 
	out << line.c_str() <<"\n";

}

const std::string TestExecutor::currentDateTime() {
	

	return "ven 14 06" ;
}