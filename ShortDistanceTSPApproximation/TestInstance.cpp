#include "TestInstance.h"
#include "SparseGraph.h"

TestInstance::TestInstance(SparseGraph* graph) {
	this->graph = graph;
	this->dimension = graph->verticesCount();
	this->optimalSolutionWeight = -1;
}

TestInstance::TestInstance(SparseGraph* graph, std::string name, double optimalSolutionWeight) {
	this->graph = graph;
	this->dimension = graph->verticesCount();
	this->optimalSolutionWeight = optimalSolutionWeight;
	this->name = name;
}