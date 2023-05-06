#include "TestInstance.h"
#include "SparseGraph.h"

TestInstance::TestInstance(SparseGraph* graph, std::string filename) {
	this->graph = graph;
	this->dimension = graph->verticesCount();
	this->optimalSolutionWeight = -1;
	this->filename = filename;
}

TestInstance::TestInstance(SparseGraph* graph, std::string name, std::string filename, double optimalSolutionWeight) {
	this->graph = graph;
	this->dimension = graph->verticesCount();
	this->optimalSolutionWeight = optimalSolutionWeight;
	this->name = name;
	this->filename = filename;
}