#pragma once
#include <vector>
#include "TestInstance.h"
#include "GraphAlgorithm.h"

class TestsRunner {
private:
	std::vector<TestInstance*> instances;
	GraphAlgorithm algorithm;
	std::string output_dir = "..\\output\\";
public:
	TestsRunner(std::vector<TestInstance*> instances, GraphAlgorithm algorithm);
	void RunTests();
private:
	double FindCycleWeight(std::vector<int> cycle, TestInstance* instance);
	void SaveToFile(std::vector<int> cycle, double weight, TestInstance* instance);
};