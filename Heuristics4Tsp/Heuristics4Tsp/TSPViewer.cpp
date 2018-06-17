#include "stdafx.h"
#include "TSPViewer.h"

#include <opencv2\opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

TSPViewer::TSPViewer()
{
}


TSPViewer::~TSPViewer()
{
}

void TSPViewer::drawTSP(const TSPSolution&  solution, const TSP& tsp, std::string window_name, int radius, int problemsize, bool filedraw, bool show) {

	int img_radius = 250;

	int scale = 220 / radius;
	int offset = 10;

	Mat img(img_radius, img_radius, CV_8UC3);
	RNG& rng = theRNG();

	char key;
	vector<Point> points;
	for (int i = 0; i < tsp.n; i++)
	{
		TSP::Point point = tsp.nodes.at(solution.sequence.at(i));
		points.push_back(Point(point.x*scale + offset, point.y*scale + offset));
	}

	img = Scalar::all(0);
	// draw tsp nodes (points) 
	for (int i = 0; i < points.size(); i++)
		circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);


	int pathsize = points.size();
	Point pt0 = points[0];
	Point ptn = points[pathsize - 1];
	// draw path lines 
	for (int i = 1; i < pathsize; i++)
	{
		Point pt = points[i];
		line(img, pt0, pt, Scalar(0, 255, 0), 1, LINE_AA);
		pt0 = pt;
	}
	line(img, points[pathsize - 1], points[0], Scalar(0, 255, 0), 1, LINE_AA);
	if (filedraw) imwrite(window_name + ".png", img);
	if (show)
	{
		imshow(window_name, img);
		key = (char)waitKey();
	}
}
