#pragma once
#include "TestInstance.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include "InstanceFileParser.h"
#define DIRECTORY_PATH "../input"

class InstancesReader {
	private:
		InstanceFileParser* parser;
	public:
		InstancesReader() {
			parser = (new MatrixFileParser())->SetNext(new NodeCoordFileParser());
		}

		std::vector<TestInstance*> Read() {
			std::string directoryPath = "../input";
			std::vector<TestInstance*> instances;

			for (auto const& dir_entry : std::filesystem::directory_iterator{ directoryPath }){
				std::string path = dir_entry.path().u8string();

				TestInstance* instance = this->parser->ParseFile(path);
				if (instance)
					instances.push_back(instance);
			}

			std::cout << "Parsed succesfully " << instances.size() << " files\n";

			return instances;
		}

};