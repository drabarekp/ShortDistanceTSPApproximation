#pragma once

#include <vector>

class NetworkGraph {
	typedef std::vector<std::vector<double>> CostMatrix;

	CostMatrix costs;

public:
	NetworkGraph(CostMatrix cost_matrix);

};