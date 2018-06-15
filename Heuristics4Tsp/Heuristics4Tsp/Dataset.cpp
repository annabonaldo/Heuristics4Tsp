#include "stdafx.h"
#include "Dataset.h"
#include <string>

std::string Dataset::baseInputFolder = "dataset\\"; 
std::string Dataset::baseOutputFolder = "dataReports\\";
std::string Dataset::randomN = "randomN";
std::string Dataset::constGrid = "constGrid";

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}

Dataset Dataset::randomNDataset()
{
	Dataset dataset; 
	dataset.name = randomN;
	dataset.output_stats = "dataReports\\RANDheuristicsStats.txt";
	std::vector<int> sizes = 
	{ 
		10, 50, 100, 200
	}; 

	for (int s = 0; s < sizes.size(); s++)
	{
		int actual_dataset_size = sizes.at(s); 
		std::string N = std::to_string(actual_dataset_size); 
		for (int i = 0 ; i < 10; i++)
		{
			std::string key = N+"sample"+std::to_string(i); 
			
			std::string input_file  = 
				"dataset\\randomN\\"+ 
				std::to_string(actual_dataset_size) +
				"RANDsample"+
				std::to_string(i).c_str()+
				"model.txt";
			dataset.input_files.insert(std::pair<std::string, std::string>(key, input_file));
			dataset.input_sizes.insert(std::pair<std::string, int>(key, actual_dataset_size));
		}
	}
	return dataset; 
}

Dataset Dataset::constGridDataset()
{

	Dataset dataset;
	dataset.name = constGrid;
	dataset.output_stats = "dataReports\\CONSTGRIDheuristicsStats.txt";

	std::string N10 = "dataset\\constGrid\\10CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("10", N10));
	dataset.input_sizes.insert(std::pair<std::string, int>("10", 10));

	std::string N50 = "dataset\\constGrid\\50CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("50", N50));
	dataset.input_sizes.insert(std::pair<std::string, int>("50", 50));

	std::string N100 ="dataset\\constGrid\\100CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("100", N100));
	dataset.input_sizes.insert(std::pair<std::string, int>("100", 100));

	std::string N200 = "dataset\\constGrid\\200CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("200", N200));
	dataset.input_sizes.insert(std::pair<std::string, int>("200", 200));
		
	return dataset; 
}

