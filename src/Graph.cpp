#include "Graph.h"
#include "utils.h"

Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::topologicalSortUtil(int v, bool visited[], bool* recStack,
                                std::stack<int>& Stack)
{
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        std::list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i] && topologicalSortUtil(*i, visited, recStack, Stack)) {
                return true;
            } else if (recStack[*i]) {
                return true;
            }
        }
    }
    
    recStack[v] = false;
    Stack.push(v);
    return false;
}

void Graph::topologicalSort(std::set<int> used_vertices, std::map<int, int> index_to_id)
{
    std::stack<int> Stack;
    int size = used_vertices.size();
    bool* visited = new bool[size];
    bool* recStack = new bool[size];
    
    for (int i = 0; i < size; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    bool hasCycle = false;
    
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            if (topologicalSortUtil(i, visited, recStack, Stack)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) {
        std::cout << "there is a cycle in current graph!" << std::endl;
    } else {
        while (Stack.empty() == false) {
            std::cout << index_to_id[Stack.top()] << " ";
            Stack.pop();
        }
        std::cout << std::endl;
    }
    
    delete[] visited;
    delete[] recStack;
}