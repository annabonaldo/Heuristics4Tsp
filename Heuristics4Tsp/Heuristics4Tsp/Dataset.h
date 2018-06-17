#pragma once
#include <vector>
#include <map>
class Dataset
{
public:
	enum ActiveDataset {
		RandActive,
		GridActive,
		ConstRand50Active,
		ConstRand5000Active,
		SemigridActive
	};
	
	std::map<std::string, int> input_sizes;
	std::map<std::string, std::string> input_files; 
	std::string output_stats; 

	static Dataset RANDN_Dataset(); 
	static Dataset GRID_Dataset(); 
	static Dataset SEMIGRID_Dataset();
	static Dataset CONSTRAND50_Dataset();
	static Dataset CONSTRAND5000_Dataset();

	
	static std::string Dataset::baseInputFolder; 
	static std::string Dataset::baseOutputFolder;

	static std::string Dataset::RANDN;
	static std::string Dataset::CONSTRAND50;
	static std::string Dataset::CONSTRAND5000;
	static std::string Dataset::GRID;
	static std::string Dataset::SEMIGRID;

	std::string name; 
	ActiveDataset type;

	Dataset();
	~Dataset();
	
private: 
	static Dataset loadDataset(const std::string & datasetName, ActiveDataset type);
};

