#pragma once

#include "Graph.h"
#include <map>
#include <vector>
#include <string>

struct GraphEdge {
	int source;
	int dest;
	double cost;

	GraphEdge(): source(0), dest(0), cost(0) {}
	GraphEdge(int source, int dest, double cost) : source(source), dest(dest), cost(cost) {}

	std::string toString() { return "(" + std::to_string(source) + " " + std::to_string(dest) + ")"; }
};

class SparseGraph: public Graph
{
	std::vector<std::map<int, double>> costs;

public:
	
	SparseGraph(std::vector<std::vector<double>> cost_matrix);
	SparseGraph(std::vector<std::map<int, double>> costs);
	SparseGraph(std::map<std::pair<int, int>, double> edges);

	double getCost(int i, int j) const;
	int edgesCount() const;
	int verticesCount() const;
	std::vector<GraphEdge> getEdges();

	void getEdgesBelowAndAboveMedian(std::map<std::pair<int, int>, double>& below, std::map<std::pair<int, int>, double>& above);
	double findMedianCost();
};

