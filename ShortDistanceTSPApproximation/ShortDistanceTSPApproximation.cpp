// ShortDistanceTSPApproximation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"
#include "SparseGraph.h"
#include "GraphAlgorithm.h"
#include "InstancesReader.h"

int main()
{

    std::vector<std::vector<double>> costs = { {0, 0.3, 2.1}, {0, 0, 1.5}, {0, 0, 0} };
    GraphAlgorithm alg;
    SparseGraph sg(costs);


    auto tree = alg.kruskalMinimalSpanningTree(sg);

    for (auto e : tree)
        std::cout << e.toString() << "\n";
    
    std::cout << sg.edgesCount();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
