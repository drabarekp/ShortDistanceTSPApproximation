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

double NetworkGraph::getCost(int i, int j) const {
	return costs[i][j];
}

int NetworkGraph::verticesCount() const{
	return costs.size();
}

int NetworkGraph::edgesCount() const{

	int count = 0;

	for (int i = 0; i < verticesCount(); i++) {
		for (int j = 0; j < verticesCount(); j++) {
			if (getCost(i, j) != NO_EDGE) count++;
		}
	}

	return count / 2;
}