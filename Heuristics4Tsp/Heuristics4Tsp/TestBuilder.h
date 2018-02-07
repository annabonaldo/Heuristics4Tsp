#pragma once
#include <string>
#include <vector>


struct Point {
	double x;
	double y;
	Point(double px, double py) : x(px), y(py) {}
};

class TestBuilder
{
public:
	TestBuilder();
	~TestBuilder();

	static std::string outDir; 

};
