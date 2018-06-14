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
#include "GreedySolver.h"
#include "TSearchSolver.h"
#include "DatasetGenerator.h"
// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	

	std::cin.ignore();

	//TSPViewer::visualizeTSP(aSolution, tspInstance, solver.name() + " before computing TSP", 2);
	//TSPViewer::visualizeTSP(endSolution, tspInstance, solver.name() + " TSP solution",2);
	
	return 0;
}

