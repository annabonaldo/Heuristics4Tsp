#include "stdafx.h"
#include "DatasetGenerator.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

std::map<std::string, TSP> DatasetGenerator::DatasetPool = std::map<std::string, TSP>();
std::vector<Dataset> DatasetGenerator::datasets = std::vector<Dataset>(); 

void DatasetGenerator::generate()
{
	datasets.push_back(Dataset::randomNDataset()); 
	datasets.push_back(Dataset::constGridDataset());
}


void DatasetGenerator::generateRandom(int n, int radius, std::string name, TSP & tsp)
{
	srand(time(NULL));

	double x, y;
	std::vector<TSP::Point> out; 
	for (int i = 0; i<n; i++)
	{
		x = rand() % radius;
		y = rand() % radius;
		std::cout << x << ", " << y << std::endl;
	
		out.push_back(TSP::Point(x, y)); 
	}
	tsp.init(out); 
	tsp.save(name); 
	DatasetPool.insert(std::pair<std::string, TSP>(name, tsp));
}

void DatasetGenerator::generateGrid(int n, double distanceH, double distanceW, int pointsH, int pointsW, std::string name, TSP & tsp)
{	
	std::vector<TSP::Point> out;
	for (int h = 0; h< pointsH; h++)
	{
		double x = h*distanceH; 
		for (int w = 0; w < pointsW; w++)
		{
			double y = w*distanceW; 
			std::cout << x << ", " << y << std::endl;
			out.push_back(TSP::Point(x, y));
		}
	}
	tsp.init(out);
	tsp.save(name);
	DatasetPool.insert(std::pair<std::string, TSP>(name, tsp));
}

void DatasetGenerator::readDataset(std::string filename, TSP & tsp)
{
	int size = 0; 
	std::vector<TSP::Point> out;
	std::ifstream in(filename.c_str());
	in >> size;
	out.resize(size);

	char* separator = ",";
	while (!in.eof())
	{
		double x, y;

		in >> x >> *separator >> y;

		std::cout << x << ", " << y << std::endl;
		out.push_back(TSP::Point(x, y)); 
	}
	tsp.init(out);
}
