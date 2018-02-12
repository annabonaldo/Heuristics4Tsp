#include "stdafx.h"
#include "TestExecution.h"
#include "TSearchSolver.h"
#include "GreedySolver.h"
#include "SimAnnealingSolver.h"
#include "StrightGreedyLineSolver.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
 bool TestExecution::RANDactive    = true;
 bool TestExecution::GRIDactive    = true;
 bool TestExecution::SEMIGRIDactive= true;
 bool TestExecution::VERBOSE = false;
 bool TestExecution::PRINT_IN_FILE = true; 
 bool TestExecution::PRINT_EX_METHOD = true;
 bool TestExecution::PRINT_DATASET = true;
 std::vector<std::string> TestExecution::results = std::vector<std::string>(); 


void TestExecution::ExecuteTest(Solver& solver)
{

	std::vector < std::string> datasets;
    if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive)     { datasets.push_back("RAND50");
						  datasets.push_back("RAND100"); 
						  datasets.push_back("RAND500"); }

	if (SEMIGRIDactive) { datasets.push_back("SEMIGRID"); }




	
	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{

		std::string problemDir =  "data\\"+*dataset+"dataset\\";
		std::string modelFile = "model.txt";
		for (int i = 5; i <= 200; i = i + 5)
		{

			string filename = problemDir + std::to_string(i) + *dataset+modelFile;
			if(PRINT_IN_FILE) cout <<*dataset  <<"--> processing file: " + filename << endl;;
			TSP tspInstance; // read Problem 
			tspInstance.read(filename.c_str(), i);

			TSPSolution aSolution(tspInstance); // build initial solution 
			solver.initRnd(aSolution); // init RANDOM soultion
			TSPSolution bestSolution(tspInstance); // build obj for best solution 
			results.push_back(*dataset +";"+solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS

			if (VERBOSE) {

				cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
				std::cout << "FROM solution: ";

				std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
				std::cout << "TO   solution: ";
				std::cout << "(Lenght value : " << solver.solutionLengthValue(bestSolution, tspInstance) << ")\n";
				cout << "------------------------------------------" << std::endl;

			}	
		}		
	}

}

void TestExecution::ExecuteTestLowPerformamces(Solver& solver)
{
	PRINT_IN_FILE = true; 
	std::vector < std::string> datasets;
	if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive) {
		datasets.push_back("RAND50");
		//datasets.push_back("RAND100");
		datasets.push_back("RAND500");
	}

	if (SEMIGRIDactive) {
		datasets.push_back("SEMIGRID");
	}



	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{

		std::string problemDir = "data\\" + *dataset + "dataset\\";
		std::string modelFile = "model.txt";
		if (PRINT_DATASET) std::cout << "Working on dataset: "<< *dataset << std::endl; 
		for (int i = 5; i <= 200; i = i + 5)
		{

			string filename = problemDir + std::to_string(i) + *dataset + modelFile;
			if (PRINT_IN_FILE) cout << *dataset << "--> processing file: " + filename << endl;;
			TSP tspInstance; // read Problem 
			tspInstance.read(filename.c_str(), i);

			TSPSolution aSolution(tspInstance); // build initial solution 
			solver.initRnd(aSolution); // init RANDOM soultion
			TSPSolution bestSolution(tspInstance); // build obj for best solution 
			results.push_back(*dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS
			
			if (VERBOSE) {

				cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
				std::cout << "FROM solution: ";

				std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
				std::cout << "TO   solution: ";
				std::cout << "(Lenght value : " << solver.solutionLengthValue(bestSolution, tspInstance) << ")\n";
				cout << "------------------------------------------" << std::endl;

			}

		}
		std::string outFile = "data\\results\\" + solver.filename() + std::string(*dataset) + std::string("2.csv");
		writeResults(outFile);
	}
	PRINT_IN_FILE = false; 
}


void TestExecution::writeResults(std::string outFile)
{
	std::ofstream file;
	file.open(outFile.c_str());
	for(int i =0; i< results.size(); i++)
		file << results.at(i) +"\n";
	file.close();
	results.clear(); 
}

void TestExecution::ExecuteTestOnTABU_SEARCH()
{
	if (PRINT_EX_METHOD) std::cout << "TABU SEARCH ----------------------------------------------" << std::endl;
	
	for (int iter = 10; iter <= 200; iter += 10)
	{
		for (int length = 10; length <= 200; length += 10)
		{
			if (PRINT_EX_METHOD)
				std::cout << "TABU SEARCH -- max iter: " << iter
				<< " tabulist length: " << length << std::endl;
			TSearchSolver solver = TSearchSolver(length, iter);
			TestExecution::ExecuteTest(solver);
		}
	}
	if (PRINT_EX_METHOD) std::cout <<"end TABU SEARCH" << std::endl << std::endl;
}

void TestExecution::ExecuteTestOnGREEDY_SEARCH()
{
	if (PRINT_EX_METHOD) std::cout << 
		"GREADY SEARCH ----------------------------------------------" << std::endl; 
	GreedySolver solver = GreedySolver();
	TestExecution::ExecuteTest(solver);
	if (PRINT_EX_METHOD) std::cout <<"end GREADY SEARCH" <<std::endl << std::endl;
}

void TestExecution::ExecuteTestOnSIM_ANNEALING() {
	if (PRINT_EX_METHOD) std::cout << "SIM_ANNEALIN SEARCH ----------------------------------------------"<< std::endl;
	for (int temperature = 100; temperature <= 1000; temperature += 450)
	{
		double delta = 0.1; 
			if (PRINT_EX_METHOD)
				std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << temperature 
				<< " delta: " << delta << std::endl;
			SimAnnealingSolver solver = SimAnnealingSolver((double)temperature, delta);
			TestExecution::ExecuteTestLowPerformamces(solver);

			delta = 0.6; 
				if (PRINT_EX_METHOD)
					std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << temperature << " delta: " << delta << std::endl;
			solver = SimAnnealingSolver((double)temperature, delta);
			TestExecution::ExecuteTestLowPerformamces(solver);

		
	}
	for (int temperature = 100; temperature <= 1000; temperature += 450)
	{
		double delta = 0.05;
		if (PRINT_EX_METHOD)
			std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << temperature
			<< " delta: " << delta << std::endl;
		SimAnnealingSolver solver = SimAnnealingSolver((double)temperature, delta);
		TestExecution::ExecuteTestLowPerformamces(solver);

	}
	if (PRINT_EX_METHOD) std::cout << "end SIM_ANNEALIN SEARCH" << std::endl << std::endl;
}

void TestExecution::ExecuteTestOnStrightGREEDYLine_SEARCH() {

	if (PRINT_EX_METHOD) std::cout << "StrightGREEDYLine_SEARCH SEARCH ----------------------------------------------" << std::endl;
		for (int angle = 10; angle <= 100; angle +=20)
		{
			if (PRINT_EX_METHOD)
				std::cout << "GREEDY STRIGHT LINE SEARCH -- angle: " 
				<< angle << " module: " << 0.0 << " offset: " << 0.0 << std::endl;
		    // mod = 0 (lineOffset = 0)
			double k = angle*0.01;
			StrightGreedyLineSolver solver = StrightGreedyLineSolver(k, 0.0, 0.0);
			TestExecution::ExecuteTest(solver);


			for (int mod = 10; mod <= 100; mod += 20)
			{
				for (int lineOffset = 10; lineOffset <= 50; lineOffset += 10)
				{
					double k = angle*0.01;
					double m = mod *0.01;
					std::cout << "GREEDY STRIGHT LINE SEARCH -- angle: "
						<< k << " module: " << m << " offset: " << lineOffset << std::endl;
					StrightGreedyLineSolver solver = StrightGreedyLineSolver(k, m,(double)lineOffset);
					TestExecution::ExecuteTest(solver);
				}
			}
		}
	if (PRINT_EX_METHOD) std::cout << "end GREADY  STRIGHT LINE SEARCH" << std::endl << std::endl;
}
