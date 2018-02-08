#include "stdafx.h"
#include "TestExecution.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
 bool TestExecution::RANDactive    = true; 
 bool TestExecution::GRIDactive    = true;   
 //bool TestExecution::SEMIGRIDactive= true; 

void TestExecution::settingsSetup()
 {
//	if(RANDactive) TestExecution::activeDatasets.push_back(DATASET_RAND);
//	if(GRIDactive) TestExecution::activeDatasets.push_back(DATASET_GRID);
 }

void TestExecution::ExecuteTest(Solver solver)
{
	
	//for (int active = 0; active < 3; active++)
	//{
	std::string problemDir = "data\\GRIDdataset\\";
	std::string solutionDir= "data\\results\\";
	std::string solutionOutFile = "TABU_GRIDresults.csv";
	std::string modelFile = "GRIDmodel.txt";

	cout << "ExecuteTest() start"; 
		std::vector<std::string> results; 
		for (int i = 5; i <= 6; i = i + 5)
		{
			
			int tabuLength = 10;                                                          /// new parameters for TS
			int maxIter = 10;
			string filename = problemDir + std::to_string(i) + modelFile;
			cout << " filename " + filename << endl;;
			TSP tspInstance; // read Problem 
			tspInstance.read(filename.c_str(), i);
		//	tspInstance.read(filename.c_str(), i);

	//		TSPSolution aSolution(tspInstance); // build initial solution 
	//		solver.initRnd(aSolution); // init RANDOM soultion
	//		cout << "problem initialized ";
	//		TSPSolution bestSolution(tspInstance); // build obj for best solution 
	//		results.push_back(solver.solve(tspInstance, aSolution, tabuLength/*new*/, maxIter/*new*/, bestSolution)); /// new parameters for TS
	//		cout << "problem solved  "; 
	//		std::cout << "FROM solution: ";
	//		aSolution.print();
	//		std::cout << "(value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
	//		std::cout << "TO   solution: ";
	//		bestSolution.print();
	//
		}
		results.push_back("prova;"); 
		writeResults(results, solutionDir+ solutionOutFile);
	}

void TestExecution::writeResults(std::vector<std::string> results, std::string outFile)
{
	std::ofstream file;
	file.open(outFile.c_str());
	for(int i =0; i< results.size(); i++)
		file << results.at(i) +"\n";
	file.close();
}


