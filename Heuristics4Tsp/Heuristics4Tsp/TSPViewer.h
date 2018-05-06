#pragma once
#include "TSPSolution.h"
class TSPViewer
{
public:
	TSPViewer();
	~TSPViewer();


	static void visualizeTSP(const TSPSolution & solution, const TSP& tsp, std::string window_name, int scale = 1);
};

