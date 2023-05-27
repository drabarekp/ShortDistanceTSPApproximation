// InstancesGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RandomInstanceGenerator.h"

int main()
{
    RandomInstanceGenerator* generator = new RandomInstanceGenerator("../generated_instances");

    int instancesSize, numberOfInstances;

    std::cout << "Provide instances size: ";
    std::cin >> instancesSize;

    std::cout << "Provide number of instances: ";
    std::cin >> numberOfInstances;

    generator->Generate(instancesSize, numberOfInstances);

#ifdef _WIN32
    system("pause");
#endif

#ifdef linux
    system("read");
#endif
}


