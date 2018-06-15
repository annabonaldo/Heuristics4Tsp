#include "stdafx.h"
#include "TSP.h"

void TSP::read(const char* filename, int size)
{
	std::ifstream in(filename);
	std::cout << filename << std::endl;
	in.open(filename);
	cost.resize(size);
	std::vector <Point> points;
	for (int i = 0; i < size; i++) {
		cost[i].reserve(size);
		int x; in >> x;
		int y; in >> y;
		points.push_back(Point(x, y));
		//	std::cout << "[" << x << " , " << y << "] ";
	}
	in.close();
	init(points);
	n = nodes.size();
	//setCosts();
}

void TSP::read(const char* filename)
{
	std::ifstream in(filename);
	// read size
	in >> n;
	std::cout << "number of nodes n = " << n << std::endl;
	// read costs
	cost.resize(n);
	for (int i = 0; i < n; i++) {
		cost[i].resize(n);
		for (int j = 0; j < n; j++) {
			double c;
			in >> c;
			cost[i][j] = c;
		}
	}
	in.close();
}

void TSP::save(std::string filename)
{
	saveCosts((filename + "Costs.dat").c_str());
	saveNodes((filename + "Nodes.csv").c_str());
}

void  TSP::saveCosts(const char* filename)
{
	std::ofstream out(filename);
	int rows = cost.size();
	if (rows > 0) {
		int size = rows*rows;
		out << "n = " << rows << ";" << std::endl;
		out << "A = " << "[" << std::endl;
		for (int i = 0; i < rows; i++)
		{
			out << "[";
			int cols = cost[i].size();
			int j = 0;
			for (j = 0; j < cols; j++)
			{
				out << (int)cost[i][j];
				if (i == j) out;
				if (j < cols - 1) out << ", ";
			}
			if (i < j)
				out << "], \n ";
			if (i == j) out << "] \n ";
		}
		out << "]; \n ";
	}

	out.close();

}

void  TSP::saveNodes(const char* filename)
{
	int size = nodes.size();
	std::ofstream out(filename);
	out << size << std::endl;

	char* separator = ";";
	for (int i = 0; i < size; i++)
		out << nodes[i].x << *separator << nodes[i].y << *separator << std::endl;

}

void  TSP::init(std::vector<Point> & points) {
	nodes.clear();
	for (int i = 0; i < points.size(); i++)
		nodes.push_back(points[i]);
	n = nodes.size(); 
	setCosts();
}

void  TSP::setCosts()
{
	int size = nodes.size();
	cost.clear(); 
	for (int i = 0; i < size; i++) {
		cost.push_back(std::vector<double>()); 		
		for (int j = 0; j < size; j++)
		{

		//	if (j != i)
			{
			
			//	std::cout << distance(i, j) << " ";
				cost[i].push_back(distance(i, j));
				
			}
		//	else
			//	cost[i][j] = 0.0;
		}
	}
}

double TSP::distance(int i, int j) const
{
	double distance = 0; 
	
	if (nodes.size() > i && nodes.size() > j) {
		Point a = nodes.at(i);
		Point b = nodes.at(j);
		distance = std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
		//std::cout <<"["<<i<< ", "<< j << "]-- [" << a.x << ", " << a.y << "]-[" << b.x << ", " << b.y << "]  distance: " << distance <<std::endl;
	}

	else
	{
		std::cout << "ERROR WITH DISTANCES OF [" << i << ", " << j << "] "<< std::endl; 
	}
	return distance; 
}

double TSP::angle(int i, int j) const
{
	Point a = nodes.at(i);
	Point b = nodes.at(j);
	double normA = std::sqrt((a.x *a.x) + (a.y *a.y));
	double normB = std::sqrt((b.x *b.x) + (b.y *b.y));
	double cos = ((a.x*b.x) + (a.y*b.y)) / (normA*normB);
	double radAngle = std::acos(cos);
	// x : 180 = radAngle : pi 
	// x = (180*radAngle)/pi ; 
	double pi = atan(1) * 4;
	return (180.0 * radAngle) / pi;
}

void  TSP::printCosts()
{
	for (int i = 0; i < cost.size(); i++)
	{
		for (int j = 0; j < cost[i].size(); j++)
			std::cout << cost[i][j] << " ";

		std::cout << std::endl;
	}
}

void  TSP::printNodes()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		TSP::Point point = nodes.at(i); 
		std::cout << i << " -- [" <<point.x << ", " <<point.y <<"]"<< std::endl;
	}
}

void  TSP::print(bool nodes, bool costs)
{
	std::cout << "TSP N size " <<this->n << std::endl; 
	if (nodes)
		printNodes(); 
	if (costs)
		printCosts(); 
}