#include "NetworkGraph.h"
#include <iostream>
#include <stdexcept>

NetworkGraph::NetworkGraph(CostMatrix &cost_matrix)
{
	if(cost_matrix.size() <= 0)
		throw std::runtime_error("error");

	if(cost_matrix.size() != cost_matrix[0].size())
		throw std::runtime_error("error");

	this->costs = cost_matrix;
}

double NetworkGraph::GetCost(int i, int j) const {
	return costs[i][j];
}