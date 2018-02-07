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

	void genereteTests()
	{	
	}

	void generateGrid(double xSize, double ySize, int xFreq, int yFreq, double xoffset = 0.0, double yoffset = 0.0)
	{
		double xDistance = xSize / xFreq; 
		double yDistance = ySize / yFreq;

		int xNUM = (int)xSize / xDistance; 
		int yNUM = (int)ySize / yDistance;

		std::vector<Point> grid; 
		grid.reserve(xNUM*yNUM); 

		double x = 0.0 + xoffset;
		double y = 0.0 + yoffset;

		for (int i = 0; i < xNUM; i++)
		{
			for (int j = 0; j < yNUM; j++)
			{
				grid.at(i*xNUM + j) = Point(x + xNUM*xDistance, y + yNUM*yDistance); 
			}
		}

	}
};
