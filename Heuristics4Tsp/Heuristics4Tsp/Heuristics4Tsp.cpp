// Heuristics4Tsp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdexcept>
#include <ctime>
#include "TestExecution.h"
#include "TSearchSolver.h"

// error status and messagge buffer
int status;
char errmsg[255];

int main(int argc, char const *argv[])
{
	try
	{
		TSearchSolver solver = TSearchSolver(10, 10); 
		TestExecution::ExecuteTest(solver); 
		std::cin.ignore();
	}
	catch (std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}

