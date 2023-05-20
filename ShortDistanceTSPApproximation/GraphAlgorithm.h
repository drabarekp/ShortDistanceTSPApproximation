#pragma once

#include "Graph.h"
#include "SparseGraph.h"
#include <list>

enum TreeSize { one, two, threeOrMore };

struct GraphAlgorithm {

public:
	
	std::vector<int> findBottleneckTSPApproximation(SparseGraph& tree);


private:
	SparseGraph kruskalMinimalSpanningTree(SparseGraph& g);
	std::list<int> recursiveBottleneckTSPApproximation(SparseGraph& tree, int root, std::vector<bool>& visited);
	TreeSize getTreeSize(SparseGraph& tree, int root, std::vector<bool>& visited);
};
