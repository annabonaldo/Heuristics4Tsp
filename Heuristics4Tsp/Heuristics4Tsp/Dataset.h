#pragma once
#include <vector>
#include <map>
class Dataset
{
public:
	enum dataset {
		dataset_randomN, 
		dataset_constGrid
	};

	std::map<std::string, std::string> input_files; 
	std::string output_stats; 

	static Dataset randomNDataset(); 
	static Dataset constGridDataset(); 

	
	static std::string Dataset::baseInputFolder; 
	static std::string Dataset::baseOutputFolder;
	static std::string Dataset::constGrid;
	static std::string Dataset::randomN;

	std::string name; 

	Dataset();
	~Dataset();
};

