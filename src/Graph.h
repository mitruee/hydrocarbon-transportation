#pragma once
#include "utils.h"
using namespace std;

class Graph {
    int V;

    list<int>* adj;

    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

public:
    Graph(int V);

    void addEdge(int v, int w);

    void topologicalSort(std::set<int> used_vertices, map<int, int> index_to_id);
};