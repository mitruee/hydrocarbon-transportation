#pragma once
#include "utils.h"
using namespace std;

// https://www.geeksforgeeks.org/cpp/cpp-program-for-topological-sorting/

class Graph {
    int V;

    list<int>* adj;

    bool topologicalSortUtil(int v, bool visited[], bool* recStack,
                                stack<int>& Stack);

public:
    Graph(int V);

    void addEdge(int v, int w);

    void topologicalSort(std::set<int> used_vertices, map<int, int> index_to_id);
};