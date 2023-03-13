#pragma once

#include "Graph.h"
#include "SparseGraph.h"

struct GraphAlgorithm {

public:
	void findBottleneckSpanningTree(Graph& g);
	std::vector<GraphEdge> kruskalMinimalSpanningTree(SparseGraph& g);
	void recusivelyFindBottleneckSpanningTree(Graph& g);

private:
	
};
