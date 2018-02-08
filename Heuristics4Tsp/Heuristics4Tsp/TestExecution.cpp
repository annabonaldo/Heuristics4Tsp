#include "stdafx.h"
#include "TestExecution.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
 bool TestExecution::RANDactive    = true; 
 bool TestExecution::GRIDactive    = true;   
 bool TestExecution::SEMIGRIDactive= true; 



void TestExecution::ExecuteTest(Solver solver)
{

	bool VERBOSE = false;
	std::vector < std::string> datasets;
    if (GRIDactive)     datasets.push_back("GRID");
	if (RANDactive)     datasets.push_back("RAND");
	if (SEMIGRIDactive) datasets.push_back("SEMIGRID");

	std::string problemDir = "data\\GRIDdataset\\";
	std::string solutionDir = "data\\results\\";
	std::string solutionFile = "results.csv";
	std::string modelFile = "GRIDmodel.txt";


	std::vector<std::string> results;
	std::vector<std::string>::iterator dataset = datasets.begin();
	for (; dataset != datasets.end(); dataset++)
	{
		for (int i = 5; i <= 200; i = i + 5)
		{

			//int tabuLength = 10;                                                          /// new parameters for TS
		//	int maxIter = 10;
			string filename = problemDir + std::to_string(i) + modelFile;
			cout <<*dataset  <<"--> processing file: " + filename << endl;;
			TSP tspInstance; // read Problem 
			tspInstance.read(filename.c_str(), i);

			TSPSolution aSolution(tspInstance); // build initial solution 
			solver.initRnd(aSolution); // init RANDOM soultion
			TSPSolution bestSolution(tspInstance); // build obj for best solution 
			results.push_back(solver.solve(tspInstance, aSolution, bestSolution)); /// new parameters for TS

			if (VERBOSE) {

				cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
				std::cout << "FROM solution: ";

				std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
				std::cout << "TO   solution: ";
				std::cout << "(Lenght value : " << solver.solutionLengthValue(bestSolution, tspInstance) << ")\n";
				cout << "------------------------------------------" << std::endl;

			}
			
		}
		std::string outFile = solver.name() +*dataset + solutionFile;
		writeResults(results, solutionDir + outFile);
		cout << std::endl << std::endl;
	}
	std::cout << "END EXECUTION " << std::endl; 
}

void TestExecution::writeResults(std::vector<std::string> results, std::string outFile)
{
	std::ofstream file;
	file.open(outFile.c_str());
	for(int i =0; i< results.size(); i++)
		file << results.at(i) +"\n";
	file.close();
}


