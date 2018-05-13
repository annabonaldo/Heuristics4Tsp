#pragma once
#include <vector>
#include "TSP.h"
#include <map>
class DatasetGenerator
{
public:
	static std::map<std::string, TSP> DatasetPool;
	static void generate(); 
	static void generateRandom(int n, int radius, std::string name, TSP & tsp);
	static void generateGrid(int n, double distanceH, double distanceW, int pointsH, int pointsW, std::string name, TSP & tsp);

	static void readDataset(std::string filename, TSP & tsp);
};

