#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class TSP
{
public:
	struct Point {
		double x;
		double y;
		Point() : x(0), y(0) {}
		Point(double a, double b) : x(a), y(b) {}
	 };


	TSP() : n(0), infinite(1e10) { }
	int n; //number of nodes
	std::vector< std::vector<double> > cost;
	std::vector<Point>                 nodes;
	double infinite; // infinite value (an upper bound on the value of any feasible solution
	
	void read(const char* filename, int size); 
	void read(const char* filename); 
	void save(std::string filename); 
	void saveCosts(const char* filename);
	void saveNodes(const char* filename);
	void init(std::vector<Point> & points);
	void setCosts();	
	double distance(int i, int j) const; 
	double angle(int i, int j) const; 
	void printCosts(); 
	
	
};

