#include "stdafx.h"
#include "DatasetGenerator.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

std::map<std::string, TSP> DatasetGenerator::DatasetPool = std::map<std::string, TSP>();

void DatasetGenerator::generate()
{
	int samplePool = 10; 

	TSP tsp1; 
	std::string key = "RANDOM10-sample" + std::to_string(0);
	generateRandom(10, 10, key,  tsp1);
	/*
	for (int i = 0; i < samplePool; i++) {
		std::vector<TSP::Point> set1;
		generateRandom(10, 10, set1);
		DatasetPool.insert(std::pair<std::string, std::vector<TSP::Point>>("RANDOM10-sample" + std::to_string(i), set1));

		std::vector<TSP::Point> set2;
		generateRandom(100, 100, set2);
		DatasetPool.insert(std::pair<std::string, std::vector<TSP::Point>>("RANDOM100-sample" + std::to_string(i), set2));

		std::vector<TSP::Point> set3;
		generateRandom(1000, 1000, set3);
		DatasetPool.insert(std::pair<std::string, std::vector<TSP::Point>>("RANDOM1000-sample"+std::to_string(i), set2);
	}*/
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
