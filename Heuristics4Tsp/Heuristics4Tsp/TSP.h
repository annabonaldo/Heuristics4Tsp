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

	void read(const char* filename)
	{
		std::ifstream in(filename);
		// read size
		in >> n;
		std::cout << "number of nodes n = " << n << std::endl;
		// read costs
		cost.resize(n);
		for (int i = 0; i < n; i++) {
			cost[i].reserve(n);
			for (int j = 0; j < n; j++) {
				double c;
				in >> c;
				cost[i].push_back(c);
			}
		}
		in.close();
	}

	double infinite; // infinite value (an upper bound on the value of any feasible solution
	
	double distance(int i, int j) const
	{
		Point a = nodes.at(i);
		Point b = nodes.at(j);
		return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
	}

	double angle(int i, int j) const
	{
		Point a = nodes.at(i);
		Point b = nodes.at(j);
		double normA = std::sqrt((a.x *a.x) + (a.y *a.y));
		double normB = std::sqrt((b.x *b.x) + (b.y *b.y));
		double cos = ((a.x*b.x) + (a.y*b.y)) / (normA*normB); 
		double radAngle =  std::acos(cos); 
		// x : 180 = radAngle : pi 
		// x = (180*radAngle)/pi ; 
		double pi = atan(1) * 4; 
		return (180.0 * radAngle) / pi;
	}

	void printCosts()
	{
		for (int i = 0; i < cost.size(); i++)
		{
			for (int j = 0; j < cost[i].size(); j++)
				std::cout << cost[i][j] << " ";

			std::cout << std::endl;
		}
	}
	
};

