#include "GraphAlgorithm.h"
#include "UnionFind.h"
#include <algorithm>

bool lesserEdge(GraphEdge e1, GraphEdge e2) {
	return e1.cost < e2.cost;
}

void GraphAlgorithm::findBottleneckSpanningTree(Graph& g) {

}

void GraphAlgorithm::recusivelyFindBottleneckSpanningTree(Graph& g) {

}

std::vector<GraphEdge> GraphAlgorithm::kruskalMinimalSpanningTree(SparseGraph& g){
	UF unionFind(g.verticesCount());
	std::vector<GraphEdge> minimalSpanningTree;

	auto edges = g.getEdges();
	std::sort(edges.begin(), edges.end(), lesserEdge);

	for (auto e : edges) {
		if (unionFind.find(e.dest) == unionFind.find(e.source)) 
			continue;

		minimalSpanningTree.push_back(GraphEdge(e.source, e.dest, e.cost));

		int s = e.source;
		int d = e.dest;

		unionFind.merge(s, d);
	}

	return minimalSpanningTree;
}

