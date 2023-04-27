#pragma once
#include "SparseGraph.h"

class TestInstance {

public:
	TestInstance(SparseGraph* graph);
	TestInstance(SparseGraph* graph, std::string name, double optimalSolutionWeight = -1);

	SparseGraph* graph;
	std::string name;
	int dimension;
	double optimalSolutionWeight = -1;

};