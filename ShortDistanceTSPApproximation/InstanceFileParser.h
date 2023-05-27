#pragma once
#include "TestInstance.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class InstanceFileParser {
private:
	InstanceFileParser* nextParser = NULL;
public:
	virtual InstanceFileParser* SetNext(InstanceFileParser* nextParser) {

		this->nextParser = nextParser;

		return this->nextParser;
	}

	virtual TestInstance* ParseFile(std::string path) {
		if (this->nextParser) {
			return this->nextParser->ParseFile(path);
		}

		return NULL;
	}

protected:
	bool CheckTriangleInequality(std::vector<std::vector<double>> cost_matrix) {
		for (int i = 0;i < cost_matrix.size();i++) {
			for (int j = 0;j < cost_matrix.size();j++) {
				for (int k = 0;k < cost_matrix.size();k++) {
					if (cost_matrix[i][j] + cost_matrix[j][k] < cost_matrix[i][k]) {
						return false;
					}
				}
			}
		}

		return true;
	}

protected:
	std::string trimLine(std::string line) {

		line.erase(0, line.find_first_not_of(' ')).erase(line.find_last_not_of(' ') + 1, line.length() - line.find_last_not_of(' '));
		line.erase(std::unique(line.begin(), line.end(), [](char c1, char c2) {return c1 == ' ' && c2 == ' ';}), line.end());

		return line;
	}
};

class MatrixFileParser : public InstanceFileParser {
	TestInstance* ParseFile(std::string path) override {

		std::string line;
		std::ifstream file(path);
		std::vector<std::vector<double>> cost_matrix;

		std::getline(file, line);
		line = this->trimLine(line);

		std::string name = "";
		if (line.rfind("NAME", 0) == 0)
		{
			name = line.substr(line.find(':') + 2);
			std::getline(file, line);
			line = this->trimLine(line);
		}

		int optimal = -1;
		if (line.rfind("OPTIMAL_WEIGHT", 0) == 0)
		{
			try {
				optimal = std::stod(line.substr(line.find(':') + 2));
			}
			catch (...) {
				return InstanceFileParser::ParseFile(path);
			}
			std::getline(file, line);
			line = this->trimLine(line);
		}

		do {
			line = this->trimLine(line);
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

		} while (std::getline(file, line) && line.find("EOF") == std::string::npos);

		int firstSize = cost_matrix.size() > 0 ? cost_matrix[0].size() : 0;

		if (cost_matrix.size() != firstSize) {
			return  InstanceFileParser::ParseFile(path);
		}
		for (int i = 0;i < cost_matrix.size();i++) {
			if (cost_matrix[i].size() != firstSize)
				return InstanceFileParser::ParseFile(path);
		}


		std::string filename = path.substr(path.find_last_of("/\\") + 1);

		if (!CheckTriangleInequality(cost_matrix)) {
			std::cout << "Triangle inequality not satisfied for file " << filename << std::endl;
			return InstanceFileParser::ParseFile(path);
		}

		std::cout << "Parsed file " << filename << std::endl;
		
		return new TestInstance(new SparseGraph(cost_matrix), name, filename, optimal);
	}
};

class LowerDiagonalMatrixFileParser : public InstanceFileParser {
	TestInstance* ParseFile(std::string path) override {

		std::string line;
		std::ifstream file(path);
		std::vector<std::vector<double>> cost_matrix;

		std::getline(file, line);
		line = this->trimLine(line);

		std::string name = "";
		if (line.rfind("NAME", 0) == 0)
		{
			name = line.substr(line.find(':') + 2);
			std::getline(file, line);
			line = this->trimLine(line);
		}

		int optimal = -1;
		if (line.rfind("OPTIMAL_WEIGHT", 0) == 0)
		{
			try {
				optimal = std::stod(line.substr(line.find(':') + 2));
			}
			catch (...) {
				return InstanceFileParser::ParseFile(path);
			}
			std::getline(file, line);
			line = this->trimLine(line);
		}

		std::vector<double> row;
		do {
			line = this->trimLine(line);
			std::stringstream line_stream(line);
			std::string number;

			while (std::getline(line_stream, number, ' ')) {
				double weight;
				try {
					weight = std::stod(number);
				}
				catch (...) {
					return InstanceFileParser::ParseFile(path);
				}
				row.push_back(weight);
				if (weight == 0.0) {
					cost_matrix.push_back(row);
					row = std::vector<double>();
				}
			}

		} while (std::getline(file, line) && line.find("EOF") == std::string::npos);

		for (int i = 1;i < cost_matrix.size();i++) {
			if (cost_matrix[i].size() != cost_matrix[i - 1].size() + 1) {
				return InstanceFileParser::ParseFile(path);
			}
		}

		for (int i = 0;i < cost_matrix.size();i++) {
			for (int j = i + 1;j < cost_matrix.size();j++) {
				cost_matrix[i].push_back(cost_matrix[j][i]);
			}
		}

		std::string filename = path.substr(path.find_last_of("/\\") + 1);

		if (!CheckTriangleInequality(cost_matrix)) {
			std::cout << "Triangle inequality not satisfied for file " << filename << std::endl;
			return InstanceFileParser::ParseFile(path);
		}

		std::cout << "Parsed file " << filename << std::endl;

		return new TestInstance(new SparseGraph(cost_matrix), name, filename, optimal);
	}
};

class NodeCoordFileParser : public InstanceFileParser {
	TestInstance* ParseFile(std::string path) override {

		std::string line;

		std::ifstream file(path);

		std::getline(file, line);
		line = this->trimLine(line);
		if (!line.rfind("NAME", 0) == 0) {
			return InstanceFileParser::ParseFile(path);
		}
		std::string name = line.substr(line.find(':') + 2);

		std::getline(file, line);
		line = this->trimLine(line);
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
		line = this->trimLine(line);

		if (line.rfind("OPTIMAL_WEIGHT", 0) == 0)
		{
			try {
				optimal = std::stod(line.substr(line.find(':') + 2));
			}
			catch (...) {
				return InstanceFileParser::ParseFile(path);
			}
			std::getline(file, line);
			line = this->trimLine(line);
		}

		if (!line.rfind("NODE_COORD_SECTION", 0) == 0) {
			return InstanceFileParser::ParseFile(path);
		}
		
		std::pair<double, double>* coords = new std::pair<double, double>[dimension];

		for (int i = 0;i < dimension;i++) {
			std::getline(file, line);
			line = this->trimLine(line);
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

		std::string filename = path.substr(path.find_last_of("/\\") + 1);

		std::cout << "Parsed file " << filename << std::endl;

		return new TestInstance(new SparseGraph(cost_matrix),name, filename, optimal);
	}

	private:
		std::vector<std::vector<double>> MakeCostMatrix(std::pair<double, double>* coords, int dimension) {
			std::vector<std::vector<double>> cost_matrix;

			for (int i = 0;i < dimension;i++) {
				cost_matrix.push_back(std::vector<double>(dimension));
			}

			for (int i = 0;i < dimension;i++) {
				for (int j = i;j < dimension;j++) {
					cost_matrix[i][j] = cost_matrix[j][i] = std::sqrt((coords[i].first - coords[j].first) * (coords[i].first - coords[j].first) +
						(coords[i].second - coords[j].second) * (coords[i].second - coords[j].second));
				}
			}

			return cost_matrix;
		}
};