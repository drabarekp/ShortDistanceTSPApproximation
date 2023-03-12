#pragma once

class Graph {

public:

	virtual double getCost(int i, int j) const = 0;
	virtual int edgesCount() const = 0;
	virtual int verticesCount() const = 0;
};