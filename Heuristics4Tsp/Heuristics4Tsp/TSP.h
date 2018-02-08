#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class TSP
{
	struct Point {
		double x;
		double y;
		Point() : x(0), y(0) {}
		Point(double a, double b) : x(a), y(b) {}
	 };

public:
	TSP() : n(0), infinite(1e10) { }
	int n; //number of nodes
	std::vector< std::vector<double> > cost;
	std::vector<Point>                 nodes;
	
	void read(const char* filename, int size)
	{
		std::ifstream in(filename);
		cost.resize(size); 
		for (int i = 0; i < size; i++) {
			cost[i].reserve(size);
			double x; in >> x;
			double y; in >> y;
			nodes.push_back(Point(x, y));
			//std::cout << "[" << x << " , " << y << "] ";
		}
		in.close();
		n = nodes.size(); 

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				if (j != i)	
					cost[i].push_back(distance(i, j));	
				else
					cost[i].push_back(0.0);
			}
		}
	} 

	double infinite; // infinite value (an upper bound on the value of any feasible solution

private: 
	double distance(int i, int j)
	{
		Point a = nodes.at(i);
		Point b = nodes.at(j);
		return (((a.x-b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
	}
};

