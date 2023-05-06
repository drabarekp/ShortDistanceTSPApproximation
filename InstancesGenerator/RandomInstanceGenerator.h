#pragma once
#include <string>
#include <random>
#include <fstream>
#include <filesystem>

class RandomInstanceGenerator {
private:
	std::string outputDirectory;
	const int maxCoord = 10000;
public:
	RandomInstanceGenerator(std::string directory) {
		this->outputDirectory = directory;
	}
	
	void Generate(int graphSize, int instancesNumber) {

		if (!std::filesystem::exists("..\\generated_instances")) {
			std::filesystem::create_directory("..\\generated_instances");
		}

		for (int i = 0;i < instancesNumber;i++) {
			std::string name = "rand-" + std::to_string(graphSize) + "(" + std::to_string(i) + ")";
			std::string path = "..\\generated_instances\\" + name + ".txt";
			std::ofstream file(path);

			file << "NAME: " << name << std::endl;
			file << "DIMENSION: " << std::to_string(graphSize) << std::endl;
			file << "NODE_COORD_SECTION" << std::endl;

			for (int i = 0;i < graphSize;i++) {
				int x = rand() % maxCoord;
				int y = rand() % maxCoord;

				file << std::to_string(i + 1) << " " << std::to_string(x) << " " << std::to_string(y) << std::endl;
			}
			file << "EOF";
			file.close();

		}
	}

};