#include "TestsRunner.h"
#include <iostream>
#include <fstream>
#include <filesystem>

TestsRunner::TestsRunner(std::vector<TestInstance*> instances, GraphAlgorithm algorithm){
	this->instances = instances;
	this->algorithm = algorithm;
}

void TestsRunner::RunTests() {
	
	std::chrono::duration<double> elapsed(0);
	for (auto instance : instances) {
		auto start = std::chrono::high_resolution_clock::now();
		auto result = algorithm.findBottleneckTSPApproximation(*(instance->graph));
		auto end = std::chrono::high_resolution_clock::now();
		elapsed += (end - start);

		double weight = FindCycleWeight(result, instance);

		std::cout << "Solution for file " << instance->filename << " is " << weight;
		if (instance->optimalSolutionWeight != -1) {
			std::cout << ", optimal is " << instance->optimalSolutionWeight << ", error is " << 100 * (weight - instance->optimalSolutionWeight) / instance->optimalSolutionWeight << "%" << std::endl;
		}
		else {
			std::cout << std::endl;
		}

		SaveToFile(result, weight, instance);
	}

	std::cout << "Total time for algorithm execution: " << elapsed.count() << "s" << std::endl;

	

}

double TestsRunner::FindCycleWeight(std::vector<int> cycle, TestInstance* instance)
{
	double weight = -1;

	for (int to = 1; to <= cycle.size(); to++){
		double cost = instance->graph->getCost(cycle[to-1], cycle[to%cycle.size()]);
		if (cost > weight)
			weight = cost;
	}

	return weight;
}

void TestsRunner::SaveToFile(std::vector<int> cycle, double weight, TestInstance* instance){

	if (!std::filesystem::exists(output_dir)) {
		std::filesystem::create_directory(output_dir);
	}

	std::string path = output_dir + instance->filename;
	std::ofstream file(path);

	if (!instance->name.empty()) {
		file << "NAME: " << instance->name << std::endl;
	}

	file << "DIMENSION: " << instance->dimension<<std::endl;

	file << "WEIGHT: " << weight << std::endl;

	file << "CYCLE: ";
	for (auto v : cycle) {
		file << v << " ";
	}
	file << std::endl;

	file << "EOF" << std::endl;

}
