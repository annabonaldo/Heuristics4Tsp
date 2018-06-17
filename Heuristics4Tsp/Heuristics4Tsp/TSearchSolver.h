#pragma once
#include "Solver.h"
#include <string>

class TSearchSolver :
	public Solver
{
public:
	/** Constructor */
	TSearchSolver(): Solver() {} 
	
	TSearchSolver(int lenght, int iter, bool mixed = false): Solver() {
		tabuLength = lenght;
		minTabuLenght = tabuLength; 
		maxIter = iter; 
		nIterChangeTabuLenght = - 1;
		maxTabuLenght = -1; 
	}	

	TSearchSolver(int minlenght,int maxlenght,int iterChangeTabuLenght, int iter, bool mixed = false) : Solver() {
		tabuLength = minlenght;
		minTabuLenght = tabuLength;
		maxIter = iter;
		nIterChangeTabuLenght = iterChangeTabuLenght;
		maxTabuLenght = iterChangeTabuLenght;
	}
	
	std::string name() override { 	
		return "TSEARCH"+ moreFeatures()+"; ListLenght; "+std::to_string(tabuLength)+"; MaxIter;"
		+ std::to_string(maxIter)+ ";" ;}

	 std::string solve(const TSP& tsp, const TSPSolution& initSol, TSPSolution& bestSol) override;
	 std::string filename() override { return  "results"; };
	 bool isDynamicTabuLenght() { return (this->maxTabuLenght > 0 && this->nIterChangeTabuLenght > 0);  }
	 std::string moreFeatures()
	 {
		 std::string dynamicTabuList = ""; 
		 if (isDynamicTabuLenght())
			 dynamicTabuList = "DynamicTL"; 
		 return Solver::moreFeatures()+ dynamicTabuList;
	 }
protected:
	
	double findBestNeighbor(const TSP& tsp, const TSPSolution& currSol, int currIter, double aspiration, TSPMove& move); 
	void increaseTSLenghtIfNecessary(int notUpdatingIter); 
	void restoreTSLenghtIfNecessary(int & notUpdatingIter); 
	int maxIter;
	int nIterChangeTabuLenght; 
	int tabuLength;
	int maxTabuLenght; 
	int minTabuLenght;
	std::vector<int>  tabuList;
	bool  initTabuList(int n) {
		for (int i = 0; i < n; ++i) {
			tabuList.push_back(-tabuLength - 1);
			// at iterarion 0, no neighbor is tabu --> iteration(= 0) - tabulistInit > tabulength --> tabulistInit < tabuLength + 0
		}
		return true;
	}
};

