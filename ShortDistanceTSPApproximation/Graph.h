#pragma once

class Graph {

public:

	virtual double GetCost(int i, int j) const = 0;
};