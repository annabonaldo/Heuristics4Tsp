#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "TSP.h"

class TSPSolution
{
public:
	std::vector<int>		sequence;
	std::string             filename;

	TSPSolution(){}
	/** Constructor
	* build a standard solution as the sequence <0, 1, 2, 3 ... n-1, 0>
	* @param tsp TSP instance
	* @return ---
	*/
	TSPSolution(const TSP& tsp) {
		sequence.reserve(tsp.n + 1);
		for (int i = 0; i < tsp.n; ++i) {
			sequence.push_back(i);
		}
		sequence.push_back(0);
	}
	/** Copy constructor
	*/
	TSPSolution(const TSPSolution& tspSol) {
		sequence.reserve(tspSol.sequence.size());
		for (int i = 0; i < tspSol.sequence.size(); ++i) {
			sequence.push_back(tspSol.sequence[i]);
		}
	}

	TSPSolution(std::string filename, std::vector<int> & path) {
		this->filename = filename;
		sequence.clear();
		for (int j = 0; j < path.size(); j++) {
			std::cout << path.at(j) << " ";
			sequence.push_back(path.at(j));
		}
		print(); 
		
	}

	void print(void) const{
		std::cout << "Prining solution data"; 
		for (int i = 0; i < sequence.size(); i++) {
			std::cout << sequence[i] << " ";
		}
	}

	/** assignment method
	* copy a solution into another one
	* @param right TSP solution to get into
	* @return ---
	*/
	TSPSolution& operator=(const TSPSolution& right) {
		// Handle self-assignment:
		if (this == &right) return *this;
		for (int i = 0; i < sequence.size(); i++) {
			sequence[i] = right.sequence[i];
		}
		return *this;
	}
};

