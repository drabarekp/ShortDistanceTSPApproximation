#pragma once
#include "SparseGraph.h"

class TestInstance {

public:
	TestInstance(SparseGraph* graph, std::string filename);
	TestInstance(SparseGraph* graph, std::string name, std::string filename, double optimalSolutionWeight = -1);

	SparseGraph* graph;
	std::string name;
	int dimension;
	double optimalSolutionWeight = -1;
	std::string filename = "";

};