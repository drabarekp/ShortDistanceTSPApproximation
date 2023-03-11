#pragma once
#include "Graph.h"
#include <vector>

typedef std::vector<std::vector<double>> CostMatrix;

class NetworkGraph: Graph {
private:
	CostMatrix costs;

public:
	NetworkGraph(CostMatrix &cost_matrix);

	double GetCost(int i, int j) const;
};