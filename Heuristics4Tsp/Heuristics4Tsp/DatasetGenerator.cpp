#include "stdafx.h"
#include "DatasetGenerator.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

std::map<std::string, TSP> DatasetGenerator::DatasetPool = std::map<std::string, TSP>();
std::vector<Dataset> DatasetGenerator::datasets = std::vector<Dataset>();

void DatasetGenerator::generate(std::vector<Dataset::ActiveDataset> & activeDatasets)
{
	datasets.clear();
	for (int i = 0; i < activeDatasets.size(); i++)
	{
		Dataset::ActiveDataset dataset = activeDatasets.at(i);
		switch (dataset)
		{
		case Dataset::ActiveDataset::GridActive:
			datasets.push_back(Dataset::GRID_Dataset());
			break;

		case Dataset::ActiveDataset::RandActive:
			datasets.push_back(Dataset::RANDN_Dataset());
			break;
		case Dataset::ActiveDataset::SemigridActive:
			datasets.push_back(Dataset::SEMIGRID_Dataset());
			break;

		case Dataset::ActiveDataset::ConstRand50Active:
			datasets.push_back(Dataset::CONSTRAND50_Dataset());
			break;
		case Dataset::ActiveDataset::ConstRand5000Active:
			datasets.push_back(Dataset::CONSTRAND5000_Dataset());
			break;
		}
	}

}
int DatasetGenerator::datasetRadius(Dataset::ActiveDataset d, int size)
{
	switch (d)
	{
	case Dataset::ActiveDataset::GridActive:
		return std::sqrt(size) + 5;
		break;

	case Dataset::ActiveDataset::RandActive:
		return size;

		/*case ActiveDataset::SemigridActive:
			datasets.push_back(Dataset::SEMIGRID_Dataset());
			break;*/

	case Dataset::ActiveDataset::ConstRand50Active:
		return 50;
	case Dataset::ActiveDataset::ConstRand5000Active:
		return 5000;
	}

	return 1;
}
void DatasetGenerator::generateRandom(int n, int radius, std::string name, TSP & tsp)
{
	srand(time(NULL));

	double x, y;
	std::vector<TSP::Point> out;
	for (int i = 0; i < n; i++)
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
	for (int h = 0; h < pointsH; h++)
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

void DatasetGenerator::readDataset(std::string filename, TSP & tsp, int size)
{
	std::vector<TSP::Point> out;
	std::ifstream fileStream(filename, std::ios::in);

	//std::cout << "Read Dataset of size " << size << std::endl; 

	while (!fileStream.eof() && size > 0) {
		int x, y;
		fileStream >> x >> y;
		//std::cout << x << ", " << y << std::endl;
		out.push_back(TSP::Point(x, y));
		size--;
	}

	//std::cout << "out.size() "<< out.size() << std::endl;
	tsp.init(out);

}
