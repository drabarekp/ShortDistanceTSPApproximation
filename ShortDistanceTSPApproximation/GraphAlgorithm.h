#pragma once

#include "Graph.h"

struct GraphAlgorithm {

public:
	void findBottleneckSpanningTree(Graph& g);

private:
	void recusivelyFindBottleneckSpanningTree(Graph& g);
};
