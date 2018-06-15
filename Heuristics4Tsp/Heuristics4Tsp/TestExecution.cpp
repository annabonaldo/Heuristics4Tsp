#include "stdafx.h"
#include "TestExecution.h"
#include "TSearchSolver.h"
#include "GreedySolver.h"
#include "SimAnnealingSolver.h"
#include "StrightGreedyLineSolver.h"
#include "TSPViewer.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
 bool TestExecution::RANDactive    = false;
 bool TestExecution::GRIDactive    = false;
 bool TestExecution::SEMIGRIDactive= false;
 bool TestExecution::VERBOSE = false;
 bool TestExecution::PRINT_IN_FILE = false; 
 bool TestExecution::PRINT_EX_METHOD = false;
 bool TestExecution::PRINT_DATASET = false;
 bool TestExecution::PT100_PROBLEM_SIZE = false;
 std::vector<std::string> TestExecution::results = std::vector<std::string>(); 


void TestExecution::ExecuteTest(Solver& solver)
{
	if (solver.isLowPerformance())
	{
		if (PT100_PROBLEM_SIZE) ExecuteTestLowPerformamcesFIXED_PROBLEM_SIZE(solver);
		else ExecuteTestLowPerformamcesALL_PROBLEM_SIZE(solver);
	}
	else {
		if (PT100_PROBLEM_SIZE) ExecuteTestFIXED_PROBLEM_SIZE(solver);
		else ExecuteTestALL_PROBLEM_SIZE(solver);
	}
	std::string outFile = "data\\results\\"+solver.filename()+"IterValues.txt";
	writeData(solver.solValues, outFile);

}

void TestExecution::ExecuteTestALL_PROBLEM_SIZE(Solver& solver)
{

	std::vector < std::string> datasets;
	if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive) {
		datasets.push_back("RAND50");
		datasets.push_back("RAND100");
		datasets.push_back("RAND500");
	}

	if (SEMIGRIDactive) { datasets.push_back("SEMIGRID"); }





	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{

		std::string problemDir = "data\\" + *dataset + "dataset\\";
		std::string modelFile = "model.txt";
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
	}

}

void TestExecution::ExecuteTestFIXED_PROBLEM_SIZE(Solver& solver)
{

	std::vector < std::string> datasets;
	if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive) {
	//	datasets.push_back("RAND50");
		datasets.push_back("RAND100");
	//	datasets.push_back("RAND500");
	}

	if (SEMIGRIDactive) { datasets.push_back("SEMIGRID"); }


	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{
		std::string problemDir = "data\\" + *dataset + "dataset\\";
		std::string modelFile = "model.txt";
		int problem_size = 100; 
		{

			string filename = problemDir + std::to_string(problem_size) + *dataset + modelFile;
			if (PRINT_IN_FILE) cout << *dataset << "--> processing file: " + filename << endl;;
			TSP tspInstance; // read Problem 
			tspInstance.read(filename.c_str(), problem_size);

			TSPSolution aSolution(tspInstance); // build initial solution 
			solver.initRnd(aSolution); // init RANDOM soultion
			TSPSolution bestSolution(tspInstance); // build obj for best solution 
			results.push_back(*dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS
			TSPViewer::drawTSP(aSolution, tspInstance, solver.name()+" before computing TSP", getViewerScaleFactor(*dataset));
			TSPViewer::drawTSP(bestSolution, tspInstance, solver.name()+" TSP solution", getViewerScaleFactor(*dataset));
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

void TestExecution::ExecuteTestLowPerformamcesALL_PROBLEM_SIZE(Solver& solver)
{
	PRINT_IN_FILE = true; 
	std::vector < std::string> datasets;
	if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive) {
		datasets.push_back("RAND50");
		datasets.push_back("RAND100");
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

void TestExecution::ExecuteTestLowPerformamcesFIXED_PROBLEM_SIZE(Solver& solver)
{
	PRINT_IN_FILE = true;
	std::vector < std::string> datasets;
	if (GRIDactive)     { datasets.push_back("GRID"); }
	if (RANDactive)     {datasets.push_back("RAND100");}
	if (SEMIGRIDactive) {datasets.push_back("SEMIGRID");}


	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{

		std::string problemDir = "data\\" + *dataset + "dataset\\";
		std::string modelFile = "model.txt";
		if (PRINT_DATASET) std::cout << "Working on dataset: " << *dataset << std::endl;

		int i = 100; 
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
		//std::string outFile = "data\\results\\" + solver.filename() + std::string(*dataset) + std::string("2.csv");
		//writeResults(outFile);
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

void TestExecution::writeData(std::vector<std::string>& data, std::string outFile)
{
	//if (data.size() > 0) {
	//	std::ofstream file;
	//	file.open(outFile.c_str());
	//	for (int i = 0; i < data.size(); i++)
	//		file << results.at(i) + "\n";
	//	file.close();
	//	data.clear();
	//}
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

void TestExecution::ExecuteTestOnTABU_SEARCHIterationNum(int lenght)
{
	if (PRINT_EX_METHOD) std::cout << "TABU SEARCH ----------------------------------------------" << std::endl;

	for (int iter = 100000; iter <= 15000000; iter += 5000000)
	{
			if (PRINT_EX_METHOD)
				std::cout << "TABU SEARCH -- max iter: " << iter
				<< " tabulist length: " << lenght << std::endl;
			TSearchSolver solver = TSearchSolver(lenght, iter);
			TestExecution::ExecuteTest(solver);
		
		
	}
	if (PRINT_EX_METHOD) std::cout << "end TABU SEARCH" << std::endl << std::endl;
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
	if (ExecuteTestALL_PROBLEM_SIZE)
	{
		std::vector<double> test = { 500000.0, 100000.0 };
		for (int j = 0; j < test.size(); j++) {
			double delta = 0.0005;
			if (PRINT_EX_METHOD)
				std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << test[j]
				<< " delta: " << delta << std::endl;
			SimAnnealingSolver solver = SimAnnealingSolver(test[j], delta);
			TestExecution::ExecuteTest(solver);

		    delta = 0.05;
			if (PRINT_EX_METHOD)
				std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << test[j]
				<< " delta: " << delta << std::endl;
			solver = SimAnnealingSolver(test[j], delta);
			TestExecution::ExecuteTest(solver);

		}
	}
	else
	{
		std::string dataset = "RAND100";
		std::string problemDir = "data\\" + dataset + "dataset\\";
		std::string modelFile = "model.txt";
		int fixedSize = 100;
		string filename = problemDir + std::to_string(fixedSize) + dataset + modelFile;

		Solver& solver = GreedySolver();


		if (PRINT_IN_FILE) cout << dataset << "--> processing file: " + filename << endl;;
		TSP tspInstance; // read Problem 
		tspInstance.read(filename.c_str(), fixedSize);
		TSPSolution aSolution(tspInstance); // build initial solution 
		solver.initRnd(aSolution); // init RANDOM soultion
		TSPSolution bestSolution(tspInstance); // build obj for best solution 

		std::vector<double> test = { 5000000000000.0, 10000000000.0 };
		for (int j = 0; j < test.size(); j++) {
			std::cout << "SimAnnealingSolver TEST: temperature " << test[j] << " delta: " << 0.005 << std::endl;
			solver = SimAnnealingSolver(test[j], 0.000005);// cooling rate 
			results.push_back(dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS
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

void TestExecution::ExecuteTestOnSIM_ANNEALINGGreedyOPT() {
	if (PRINT_EX_METHOD) std::cout << "SIM_ANNEALIN SEARCH ----------------------------------------------" << std::endl;

	//std::vector<double> test = {500000.0, 100000.0}; 
	//for (int j = 0; j < test.size(); j++) {
	//
	//		
	//	double delta = 0.0005; 
	//		if (PRINT_EX_METHOD)
	//			std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << test[j]
	//			<< " delta: " << delta << std::endl;
	//		SimAnnealingSolver solver = SimAnnealingSolver(test[j], delta);
	//		//solver.verbose = true; 
	//		TestExecution::ExecuteTest(solver);
	//
	//	/*	delta = 0.6; 
	//			if (PRINT_EX_METHOD)
	//				std::cout << "SIM_ANNEALIN SEARCH -- max temperature: " << test[j] << " delta: " << delta << std::endl;
	//		solver = SimAnnealingSolver(test[j], delta);
	//		TestExecution::ExecuteTest(solver);*/
	//
	//	
	//}
	std::string dataset = "RAND100";

	std::string problemDir = "data\\" + dataset + "dataset\\";
	std::string modelFile = "model.txt";
	int fixedSize = 100;
	string filename = problemDir + std::to_string(fixedSize) + dataset + modelFile;

	Solver& solver = GreedySolver();


	if (PRINT_IN_FILE) cout << dataset << "--> processing file: " + filename << endl;;
	TSP tspInstance; // read Problem 
	tspInstance.read(filename.c_str(), fixedSize);

	TSPSolution aSolution(tspInstance); // build initial solution 
	solver.initRnd(aSolution); // init RANDOM soultion
	TSPSolution bestSolution(tspInstance); // build obj for best solution 
	if (true) {
		solver.solve(tspInstance, aSolution, bestSolution);
		aSolution = bestSolution;
	}

	std::vector<double> test = { 5000000000000.0, 10000000000.0 };
	for (int j = 0; j < test.size(); j++) {
		std::cout << "SimAnnealingSolver TEST: temperature " << test[j] << " delta: " << 0.005 << std::endl;
		solver = SimAnnealingSolver(test[j], 0.000005);// cooling rate 
		results.push_back(dataset + ";" + solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS
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


int TestExecution::getViewerScaleFactor(std::string  dataset) {
	if (dataset == "RAND50")  return 10; 
	if (dataset == "RAND100") return 5; 
	if (dataset == "RAND500") return 1; 
	if (dataset == "GRID")    return 5 ;
	if (dataset == "SEMIGRID") return 1;

}
