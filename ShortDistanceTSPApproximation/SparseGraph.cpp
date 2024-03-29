#include "SparseGraph.h"
#include <algorithm>


SparseGraph::SparseGraph(std::vector<std::vector<double>> cost_matrix) {

	int costMatrixSize = cost_matrix.size();

	this->costs.resize(costMatrixSize);

	for (int i = 0; i < costMatrixSize; i++) {
		for (int j = 0; j < costMatrixSize; j++) {
			//if(i < j)
			costs[i].emplace(j, cost_matrix[i][j]);
		}
	}
}

SparseGraph::SparseGraph(std::vector<std::map<int, double>> costs) {
	this->costs = std::vector<std::map<int, double>>(costs.size());

	for (int i = 0; i < costs.size(); i++) {
		this->costs[i] = std::map<int, double>();
		auto it = costs[i].begin();

		while (it != costs[i].end())
		{
			this->costs[i][it->first] = it->second;
			++it;
		}
	}
}

/*SparseGraph::SparseGraph(std::map<std::pair<int, int>, double> edges) {

	this->costs = std::vector<std::map<int, double>>(costs.size());
	auto it = edges.begin();

	while (it != edges.end()) {
		//if(it->first.first < it->first.second)
		this->costs[it->first.first][it->first.second] = it->second;
		//else
		this->costs[it->first.second][it->first.first] = it->second;
		++it;
	}

}*/

SparseGraph::SparseGraph(std::vector<GraphEdge> edges) {
	int maxVertexIndex = 0;
	for (auto edge : edges) {
		if (edge.dest > maxVertexIndex) maxVertexIndex = edge.dest;
		if (edge.source > maxVertexIndex) maxVertexIndex = edge.source;
	}

	this->costs = std::vector<std::map<int, double>>(maxVertexIndex + 1);
	auto it = edges.begin();
	std::vector<std::map<int, double>> costs;

	while (it != edges.end()) {
		//if (it->source < it->dest)
		this->costs[it->source][it->dest] = it->cost;
		//else
		this->costs[it->dest][it->source] = it->cost;
		++it;
	}
}

double SparseGraph::getCost(int i, int j) const {
	auto it = costs[i].find(j);
	if (it == costs[i].end())
		return -1;
	return it -> second;
}

int SparseGraph::verticesCount() const {
	return costs.size();
}

int SparseGraph::edgesCount() const {
	int count = 0;

	for (int i = 0; i < verticesCount(); i++) {
		count += costs[i].size();
	}

	return count;
}

std::vector<int> SparseGraph::getNeighbours(int from) {
	auto it = costs[from].begin();
	std::vector<int> neighbours;

	while (it != costs[from].end()) {
		neighbours.push_back(it->first);
		++it;
	}
	return neighbours;
}

void SparseGraph::getEdgesBelowAndAboveMedian(std::map<std::pair<int, int>, double>& below, std::map<std::pair<int, int>, double>& above) {
	std::map<std::pair<int, int>, double> below_local;
	std::map<std::pair<int, int>, double> above_local;

}

double SparseGraph::findMedianCost() {
	std::vector<double> costs_vector;
	for (int i = 0; i < verticesCount(); i++) {
		auto it = this->costs[i].begin();
		while (it != costs[i].end()){
			costs_vector.push_back(it->second);
			++it;
		}
	}

	std::sort(costs_vector.begin(), costs_vector.end());
	return costs_vector[costs_vector.size() / 2];
}

std::vector<GraphEdge> SparseGraph::getEdges(){
	std::vector<GraphEdge> edges;
	for (int i = 0; i < verticesCount(); i++) {
		auto it = costs[i].begin();
		while (it != costs[i].end()) {
			edges.push_back(GraphEdge(i, it->first, it->second));
			++it;
		}
	}

	return edges;
}