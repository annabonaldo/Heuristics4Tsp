// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdexcept>
#include <ctime>

#include "Solver.h"

// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	try
	{
		int tabuLength = 10;                                                          /// new parameters for TS
		int maxIter = 10;
		char* filename = "tsp12.dat";
		/// create the instance (reading data)
		TSP tspInstance;
		tspInstance.read(filename);
		TSPSolution aSolution(tspInstance);

		/// initialize clocks for running time recording
		///   two ways:
		///   1) CPU time (t2 - t1)
		clock_t t1, t2;
		t1 = clock();
		///   2) wall-clock time (tv2 - tv1)
	//truct timeval  tv1, tv2;
	//ettimeofday(&tv1, NULL);

		/// create solver class
		Solver tspSolver;
		/// initial solution (random)
		tspSolver.initRnd(aSolution);

		/// run the neighbourhood search

		TSPSolution bestSolution(tspInstance);
		tspSolver.solve(tspInstance, aSolution, tabuLength/*new*/, maxIter/*new*/, bestSolution); /// new parameters for TS

		/// final clocks
		t2 = clock();
	   //	gettimeofday(&tv2, NULL);
	
		// read ExactTSP solution 
		
		// generate multiple solution traslations
		
		
		// uses tabusearches on complex solution 
		
		

		std::cout << "FROM solution: ";
		aSolution.print();
		std::cout << "(value : " << tspSolver.evaluate(aSolution, tspInstance) << ")\n";
		std::cout << "TO   solution: ";
		bestSolution.print();
		std::cout << "(value : " << tspSolver.evaluate(bestSolution, tspInstance) << ")\n";
		//std::cout << "in " << (double)(tv2.tv_sec + tv2.tv_usec*1e-6 - (tv1.tv_sec + tv1.tv_usec*1e-6)) << " seconds (user time)\n";
		std::cout << "in " << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds (CPU time)\n";
		std::cin.ignore();
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}

