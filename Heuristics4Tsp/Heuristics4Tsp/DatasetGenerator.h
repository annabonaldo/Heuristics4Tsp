#pragma once
#include <vector>
#include "TSP.h"
#include <map>
#include "Dataset.h"
class DatasetGenerator
{
public:
	

	static std::map<std::string, TSP> DatasetPool;
	static void generate(std::vector<Dataset::ActiveDataset> & activeDatasets); 
	static void generateRandom(int n, int radius, std::string name, TSP & tsp);
	static void generateGrid(int n, double distanceH, double distanceW, int pointsH, int pointsW, std::string name, TSP & tsp);
	static int  datasetRadius(Dataset::ActiveDataset d, int size);
	static void readDataset(std::string filename, TSP & tsp, int size);
	static std::vector<Dataset> datasets; 
};

