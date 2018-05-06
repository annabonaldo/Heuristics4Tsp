#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "TSPSolution.h"
using namespace std;
class DataFileParser
{
public:
	DataFileParser();
	~DataFileParser();

	static void read(string filename, int size )
	{
		std::cout << "begin read " << std::endl;
		int realsize = size - 1; 
		std::map<int, int> path; 

		ifstream myfile;
		myfile.open(filename); 
		std::cout << "file opened " << std::endl;
		
		int i = 0; 
		int j = 0;

		string one = "1"; 
		string zero = "0";

		std::cout << "start" << std::endl; 
		if (myfile.is_open())
		{

	//		std::cout << "file opened" << std::endl; 
			char c; 
			myfile.get(c); 
	//		std::cout << "get char" << std::endl;
			while (c != ']' && c != EOF && i < size)
			{
	//			std::cout << c << " "; 
				if ('1' == c)
				{
					if (i < j) {
						std::cout << "[" << i << ", " << j<< "]**";
						path.insert(std::pair<int, int>(i, j));
					}
					else {
						std::cout << "["<<i<< ", "<< j + 1 << "]**";
						path.insert(std::pair<int, int>(i, j + 1));
					}
				}

				if ('0'== c)
				{
				//	std::cout << "0 found " << std::endl;
					if (j == realsize) 
					{ 
						i++; 
						j = 0; 
					}
					else j++; 
					
				}
				myfile.get(c); 
			}
		}
	
		int key = 0;
		std::vector<int> sequence = std::vector<int>(); 
		std::cout << path.size() << std::endl; 
		while (!path.empty()) {
			if (path.find(key) != path.end()) {
				sequence.push_back(key);
				int old_key = key; 
				key = path.at(old_key);
			//	std::cout << key << " "; 
				path.erase(old_key);
				std::cout << key<< " "<< path.size() << std::endl;
			}
		}
		TSPSolution solution = TSPSolution(filename, sequence); 
		myfile.close();
		std::cin.ignore(); 
	}

	
};

