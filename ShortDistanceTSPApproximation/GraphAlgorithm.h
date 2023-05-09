#pragma once

#include "Graph.h"
#include "SparseGraph.h"

enum TreeSize { one, two, threeOrMore };

struct GraphAlgorithm {

public:
	
	std::vector<int> findBottleneckTSPApproximation(SparseGraph& tree);


private:
	SparseGraph kruskalMinimalSpanningTree(SparseGraph& g);
	void recursiveBottleneckTSPApproximation(SparseGraph& tree, int root, std::vector<bool>& visited, std::vector<int>& cycle);
	TreeSize getTreeSize(SparseGraph& tree, int root, std::vector<bool>& visited);
};
