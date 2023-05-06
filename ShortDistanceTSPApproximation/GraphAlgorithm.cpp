#include "GraphAlgorithm.h"
#include "UnionFind.h"
#include <algorithm>
#include <numeric>
#include <iostream>

bool lesserEdge(GraphEdge e1, GraphEdge e2) {
	return e1.cost < e2.cost;
}

void GraphAlgorithm::findBottleneckSpanningTree(Graph& g) {

}

void GraphAlgorithm::recusivelyFindBottleneckSpanningTree(Graph& g) {

}

SparseGraph GraphAlgorithm::kruskalMinimalSpanningTree(SparseGraph& g){
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

	return SparseGraph(minimalSpanningTree);
}

std::vector<int> GraphAlgorithm::findBottleneckTSPApproximation(SparseGraph& tree) {
	/*
	auto visited = std::vector<bool>(tree.verticesCount());
	auto cycle = std::vector<int>();
	auto hamiltonCycle = recursiveBottleneckTSPApproximation(tree, 0, visited, cycle);*/

	auto hamiltonCycle = std::vector<int>();
	for (int i = 0;i < tree.verticesCount();i++) {
		hamiltonCycle.push_back(i);
	}
	return hamiltonCycle;
}

TreeSize GraphAlgorithm::getTreeSize(SparseGraph& tree, int root, std::vector<bool>& visited) {
	auto neighbours = tree.getNeighbours(root);
	int numOfNeighbours = std::accumulate(neighbours.begin(), neighbours.end(), 0,
		[&, visited](int sum, int second)
		{
			if (visited[second])
				return sum;
			return sum + 1;
		});

	if (numOfNeighbours == 0) {
		return one;
	}
	else if (numOfNeighbours == 1) {
		auto childsNeighbours = tree.getNeighbours(neighbours[0]);
		int numOfChildsNeighboursExceptParent = std::accumulate(childsNeighbours.begin(), childsNeighbours.end(), 0,
			[&, visited](int sum, int second)
			{
				if (visited[second])
					return sum;
				return sum + 1;
			}
		) - 1;

		if (numOfChildsNeighboursExceptParent == 0) {
			return two;
		}
		else {
			return threeOrMore;
		}
	}
	else {
		return threeOrMore;
	}
}

std::vector<int>& GraphAlgorithm::recursiveBottleneckTSPApproximation(SparseGraph& tree, int root, std::vector<bool>& visited, std::vector<int>& cycle) {
	auto treeSize = getTreeSize(tree, root, visited);
	std::vector<int> resultPath;

	if (treeSize == one) {
		resultPath.push_back(root);
		return resultPath;
	}
	else if (treeSize == two) {
		resultPath.push_back(root);
		auto neighbours = tree.getNeighbours(root);
		for (auto neighbour : neighbours) {
			if (!visited[neighbour]) {
				resultPath.push_back(neighbour);
				break;
			}
		}

		return resultPath;
	}
	else if (treeSize == threeOrMore) {

	}


	visited[root] = true;
}