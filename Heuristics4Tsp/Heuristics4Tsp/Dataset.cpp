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
	dataset.output_stats = ""; 
	std::vector<int> sizes = { 10, 50 , 100, 200 };
	for (int s = 0; s < sizes.size(); s++)
	{
		int actual_dataset_size = sizes.at(s); 
		std::string N = std::to_string(actual_dataset_size); 
		for (int i = 0; i < 10; i++)
		{
			std::string key = N.append("sample").append(std::to_string(i)); 
			std::string input_file  = baseInputFolder.c_str() + Dataset::randomN +"\\"+N.c_str() +"RANDsample"+std::to_string(i).c_str()+"model.txt";
			dataset.input_files.insert(std::pair<std::string, std::string>(key, input_file));
		}
	}
	return dataset; 
}

Dataset Dataset::constGridDataset()
{

	Dataset dataset;
	dataset.name = constGrid;
	dataset.output_stats = "";

	std::string N10 = baseInputFolder.append( "constGrid\\10CONSTGRIDsample1model.txt");
	dataset.input_files.insert(std::pair<std::string, std::string>("10", N10));

	std::string N50 = baseInputFolder.append("constGrid\\10CONSTGRIDsample1model.txt");
	dataset.input_files.insert(std::pair<std::string, std::string>("50", N50));

	std::string N100 = baseInputFolder.append("constGrid\\10CONSTGRIDsample1model.txt");
	dataset.input_files.insert(std::pair<std::string, std::string>("100", N100));

	std::string N200 = baseInputFolder.append("constGrid\\10CONSTGRIDsample1model.txt");
	dataset.input_files.insert(std::pair<std::string, std::string>("200", N200));
		
	return dataset; 
}

