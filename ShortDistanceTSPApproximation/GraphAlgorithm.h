#pragma once

#include "Graph.h"
#include "SparseGraph.h"

enum TreeSize { one, two, threeOrMore };

struct GraphAlgorithm {

public:
	void findBottleneckSpanningTree(Graph& g);
	SparseGraph kruskalMinimalSpanningTree(SparseGraph& g);
	void recusivelyFindBottleneckSpanningTree(Graph& g);
	std::vector<int>& findBottleneckTSPApproximation(SparseGraph& tree);


private:
	std::vector<int>& recursiveBottleneckTSPApproximation(SparseGraph& tree, int root, std::vector<bool>& visited, std::vector<int>& cycle);
	TreeSize getTreeSize(SparseGraph& tree, int root, std::vector<bool>& visited);
};
