#include "GraphAlgorithm.h"
#include "UnionFind.h"
#include <algorithm>
#include <numeric>
#include <iostream>

bool lesserEdge(GraphEdge e1, GraphEdge e2) {
	return e1.cost < e2.cost;
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

std::vector<int> GraphAlgorithm::findBottleneckTSPApproximation(SparseGraph& network) {

	auto tree = kruskalMinimalSpanningTree(network);
	auto visited = std::vector<bool>(tree.verticesCount());
	auto cycle = std::vector<int>();

	recursiveBottleneckTSPApproximation(tree, 0, visited, cycle);

	return cycle;
}

TreeSize GraphAlgorithm::getTreeSize(SparseGraph& tree, int root, std::vector<bool>& visited) {
	auto neighbours = tree.getNeighbours(root);
	/*int numOfNeighbours = std::accumulate(neighbours.begin(), neighbours.end(), 0,
		[&, visited](int sum, int second)
		{
			if (visited[second])
				return sum;
			return sum + 1;
		});*/
	std::vector<int> unvisitedNeighbours;
	std::copy_if(neighbours.begin(), neighbours.end(), std::back_inserter(unvisitedNeighbours), [visited](int i) {return !visited[i]; });

	if (unvisitedNeighbours.size() == 0) {
		return one;
	}
	else if (unvisitedNeighbours.size() == 1) {
		auto childsNeighbours = tree.getNeighbours(unvisitedNeighbours[0]);
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

void GraphAlgorithm::recursiveBottleneckTSPApproximation(SparseGraph& tree, int root, std::vector<bool>& visited, std::vector<int>& cycle) {
	auto treeSize = getTreeSize(tree, root, visited);
	visited[root] = true;
	//std::vector<int> resultPath;

	if (treeSize == one) {
		cycle.push_back(root);
		/*return resultPath; */
	}
	else if (treeSize == two) {
		cycle.push_back(root);
		auto neighbours = tree.getNeighbours(root);
		for (auto neighbour : neighbours) {
			if (!visited[neighbour]) {
				cycle.push_back(neighbour);
				visited[neighbour] = true;
				break;
			}
		}

		//return resultPath;
	}
	else if (treeSize == threeOrMore) {
		cycle.push_back(root);
		auto neighbours = tree.getNeighbours(root);
		for (auto neighbour : neighbours) {
			if (!visited[neighbour]) {
				recursiveBottleneckTSPApproximation(tree, neighbour, visited, cycle);
			}
		}
	}
}