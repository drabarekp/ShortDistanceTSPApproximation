#pragma once
#include "TestInstance.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class InstanceFileParser {
private:
	InstanceFileParser* nextParser;
public:
	virtual InstanceFileParser* SetNext(InstanceFileParser* nextParser) {

		this->nextParser = nextParser;

		return this;
	}

	virtual TestInstance* ParseFile(std::string path) {
		if (this->nextParser) {
			return this->nextParser->ParseFile(path);
		}

		return NULL;
	}
};

class MatrixFileParser : public InstanceFileParser {
	TestInstance* ParseFile(std::string path) override {

		std::string line;
		std::ifstream file(path);
		std::vector<std::vector<double>> cost_matrix;

		while (std::getline(file, line)) {
			std::stringstream line_stream(line);
			std::string number;
			std::vector<double> row;

			while (std::getline(line_stream, number, ' ')) {
				double weight;
				try {
					weight = std::stod(number);
				}
				catch (...) {
					return InstanceFileParser::ParseFile(path);
				}
				row.push_back(weight);
			}
			cost_matrix.push_back(row);

			int firstSize = cost_matrix.size() > 0 ? cost_matrix[0].size() : 0;
			for (int i = 0;i < cost_matrix.size();i++) {
				if (cost_matrix[i].size() != firstSize)
					return InstanceFileParser::ParseFile(path);
			}
		}

		
		return new TestInstance(new SparseGraph(cost_matrix));
	}
};

class NodeCoordFileParser : public InstanceFileParser {
	TestInstance* ParseFile(std::string path) override {

		std::string line;

		std::ifstream file(path);

		std::getline(file, line);
		if (!line.rfind("NAME", 0) == 0) {
			return InstanceFileParser::ParseFile(path);
		}
		std::string name = line.substr(line.find(':') + 2);

		std::getline(file, line);
		if (!line.rfind("DIMENSION", 0) == 0) {
			return InstanceFileParser::ParseFile(path);
		}
		int dimension;

		try {
			dimension = std::stoi(line.substr(line.find(':') + 2));
		}
		catch (...) {
			return InstanceFileParser::ParseFile(path);
		}

		double optimal = -1;

		std::getline(file, line);

		if (line.rfind("OPTIMAL_WEIGHT", 0) == 0)
		{
			try {
				optimal = std::stod(line.substr(line.find(':') + 2));
			}
			catch (...) {
				return InstanceFileParser::ParseFile(path);
			}
			std::getline(file, line);
		}

		if (!line.rfind("NODE_COORD_SECTION", 0) == 0) {
			return InstanceFileParser::ParseFile(path);
		}
		
		std::pair<double, double>* coords = new std::pair<double, double>[dimension];

		for (int i = 0;i < dimension;i++) {
			std::getline(file, line);
			if (std::count(line.begin(), line.end(), ' ') != 2) {
				return InstanceFileParser::ParseFile(path);
			}

			int vertex;
			double x_coord, y_coord;

			try {
				vertex = std::stoi(line.substr(0,line.find(' ')));
				x_coord = std::stod(line.substr(line.find(' ') + 1, line.find_last_of(' ') - line.find(' ') - 1));
				y_coord = std::stod(line.substr(line.find_last_of(' ') + 1));
			}
			catch (...) {
				return InstanceFileParser::ParseFile(path);
			}

			coords[vertex - 1] = std::make_pair(x_coord, y_coord);

		}

		std::vector<std::vector<double>> cost_matrix = MakeCostMatrix(coords, dimension);
		
		delete[] coords;

		return new TestInstance(new SparseGraph(cost_matrix),name, -1);
	}

	private:
		std::vector<std::vector<double>> MakeCostMatrix(std::pair<double, double>* coords, int dimension) {
			std::vector<std::vector<double>> cost_matrix;

			for (int i = 0;i < dimension;i++) {
				cost_matrix.push_back(std::vector<double>(dimension));
			}

			for (int i = 0;i < dimension;i++) {
				for (int j = i;j < dimension;j++) {
					cost_matrix[i][j] = cost_matrix[j][i] = round(sqrt((coords[i].first - coords[j].first) * (coords[i].first - coords[j].first) +
						(coords[i].second - coords[j].second) * (coords[i].second - coords[j].second)));
				}
			}

			return cost_matrix;
		}
};