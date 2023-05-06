#include "TestsRunner.h"
#include <iostream>
#include <fstream>


TestsRunner::TestsRunner(std::vector<TestInstance*> instances, GraphAlgorithm algorithm){
	this->instances = instances;
	this->algorithm = algorithm;
}

void TestsRunner::RunTests() {
	for (auto instance : instances) {
		auto result = algorithm.findBottleneckTSPApproximation(*(instance->graph));

		double weight = FindCycleWeight(result, instance);

		SaveToFile(result, weight, instance);
	}
}

double TestsRunner::FindCycleWeight(std::vector<int> cycle, TestInstance* instance)
{
	double weight = 0.0;

	for (int to = 1; to < cycle.size(); to++){
		weight += instance->graph->getCost(cycle[to-1], to);
	}
	weight += instance->graph->getCost(cycle[cycle.size() - 1], cycle[0]);

	return weight;
}

void TestsRunner::SaveToFile(std::vector<int> cycle, double weight, TestInstance* instance){

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
