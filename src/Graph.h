#pragma once
#include "utils.h"

// https://www.geeksforgeeks.org/cpp/cpp-program-for-topological-sorting/
// https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-greedy-algo-7/

class Graph {
    int V;

    std::list<int>* adj;
    std::map<std::pair<int, int>, float> edge_weights;

    bool topologicalSortUtil(int v, bool visited[], bool* recStack,
                                std::stack<int>& Stack);

public:
    Graph(int V);

    void addEdge(int v, int w);
    void addEdge(int v, int w, float weight);

    void topologicalSort(std::set<int> used_vertices, std::map<int, int> index_to_id);
    
    std::vector<int> dijkstra(int start, int target, std::map<int, int> index_to_id);
};
