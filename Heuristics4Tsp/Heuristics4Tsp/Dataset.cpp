#include "stdafx.h"
#include "Dataset.h"
#include <string>

std::string Dataset::baseInputFolder = "dataset\\"; 
std::string Dataset::baseOutputFolder = "dataReports\\";


std::string Dataset::RANDN = "RANDN"; 
std::string Dataset::CONSTRAND50 = "CONSTRAND50"; 
std::string Dataset::CONSTRAND5000 = "CONSTRAND5000"; 
std::string Dataset::GRID = "GRID"; 
std::string Dataset::SEMIGRID = "SEMIGRID"; 

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}

Dataset Dataset::RANDN_Dataset()
{
	Dataset dataset; 
	dataset.name = RANDN;
	dataset.type = ActiveDataset::RandActive; 
	dataset.output_stats = "dataReports\\RANDNheuristicsStats.txt";
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
				"dataset\\RANDN\\"+ 
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

Dataset Dataset::GRID_Dataset()
{

	Dataset dataset;
	dataset.name = GRID;
	dataset.type = ActiveDataset::GridActive; 
	dataset.output_stats = "dataReports\\GRIDheuristicsStats.txt";

	std::string N10 = "dataset\\GRID\\10CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("10", N10));
	dataset.input_sizes.insert(std::pair<std::string, int>("10", 10));

	std::string N50 = "dataset\\GRID\\50CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("50", N50));
	dataset.input_sizes.insert(std::pair<std::string, int>("50", 50));

	std::string N100 ="dataset\\GRID\\100CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("100", N100));
	dataset.input_sizes.insert(std::pair<std::string, int>("100", 100));

	std::string N200 = "dataset\\GRID\\200CONSTGRIDsample1model.txt";
	dataset.input_files.insert(std::pair<std::string, std::string>("200", N200));
	dataset.input_sizes.insert(std::pair<std::string, int>("200", 200));
		
	return dataset; 
}

Dataset Dataset::SEMIGRID_Dataset()
{
	return loadDataset(SEMIGRID, ActiveDataset::SemigridActive);
}
Dataset Dataset::CONSTRAND50_Dataset()
{

	return loadDataset(CONSTRAND50, ActiveDataset::ConstRand50Active);
}
Dataset Dataset::CONSTRAND5000_Dataset()
{
	return  loadDataset(CONSTRAND5000, ActiveDataset::ConstRand5000Active);
	
}

Dataset Dataset::loadDataset(const std::string & datasetName, ActiveDataset type)
{
	Dataset dataset;
	dataset.name = datasetName;
	dataset.type = type; 
	dataset.output_stats = "dataReports\\" + datasetName + "heuristicsStats.txt";
	std::vector<int> sizes =
	{
		10, 50, 100, 200
	};

	for (int s = 0; s < sizes.size(); s++)
	{
		int actual_dataset_size = sizes.at(s);
		std::string N = std::to_string(actual_dataset_size);

		for (int i = 0; i < 10; i++)
		{
			std::string key = N + "sample" + std::to_string(i);

			std::string input_file =
				"dataset\\" + datasetName + "\\" +
				std::to_string(actual_dataset_size) +
				datasetName + "sample" +
				std::to_string(i).c_str() +
				"model.txt";
			dataset.input_files.insert(std::pair<std::string, std::string>(key, input_file));
			dataset.input_sizes.insert(std::pair<std::string, int>(key, actual_dataset_size));
		}
	}
	return dataset;
}