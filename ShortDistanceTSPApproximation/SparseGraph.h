#pragma once

#include "Graph.h"
#include <map>
#include <vector>

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

	void getEdgesBelowAndAboveMedian(std::map<std::pair<int, int>, double>& below, std::map<std::pair<int, int>, double>& above);
	double findMedianCost();
};
