#pragma once
#include "TSPSolution.h"
class TSPViewer
{
public:
	TSPViewer();
	~TSPViewer();


	static void drawTSP(const TSPSolution & solution, const TSP& tsp, std::string window_name, int radius, int problemsize , bool filedraw = true, bool show = false);
};

