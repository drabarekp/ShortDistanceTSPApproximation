#pragma once
#include "Graph.h"
#include <vector>

typedef std::vector<std::vector<double>> CostMatrix;

class NetworkGraph: public Graph {

	const int NO_EDGE = INT_MIN;
private:
	CostMatrix costs;

public:
	NetworkGraph(CostMatrix &cost_matrix);

	double getCost(int i, int j) const;
	int edgesCount() const;
	int verticesCount() const;
};