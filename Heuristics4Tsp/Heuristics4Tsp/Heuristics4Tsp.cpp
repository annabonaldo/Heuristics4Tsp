// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <ctime>
#include "TestExecution.h"
#include <math.h>
#include <opencv2\opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "DataFileParser.h"
#include "TSearchSolver.h"
#include "GreedySolver.h"
#include "TSPViewer.h"
// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 10; i++) {
		std::string  filename = "data\\tsp12.dat";
		int size = 100;
		std::cout << "program start " << std::endl;
		TSP tspInstance;
		tspInstance.read("data\\tsp12.dat");
		TSPSolution aSolution(tspInstance);
		TSPSolution endSolution(tspInstance);
		srand(201+i*rand());
		GreedySolver solver = GreedySolver(); // 10000000, 100);
		solver.initRnd(aSolution);
		solver.solve(tspInstance, aSolution, endSolution);
		srand(201 + i*rand());
		TSearchSolver solver2 = TSearchSolver(1000000, 10000);
		solver2.solve(tspInstance, endSolution, endSolution);
	
		solver2.solve(tspInstance, endSolution, endSolution);
		cout << "Solved problem --  size:  " << tspInstance.n << std::endl;
		std::cout << "FROM solution: ";

		std::cout << "(Lenght value : " << solver.solutionLengthValue(aSolution, tspInstance) << ")\n";
		std::cout << "TO   solution: ";
		std::cout << "(Lenght value : " << solver.solutionLengthValue(endSolution, tspInstance) << ")\n";
		cout << "------------------------------------------" << std::endl;
	}
	cin.ignore();

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

