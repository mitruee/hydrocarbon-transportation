#include "Graph.h"
#include "utils.h"

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    Stack.push(v);
}

void Graph::topologicalSort(std::set<int> used_vertices, map<int, int> index_to_id)
{
    stack<int> Stack;
    bool* visited = new bool[used_vertices.size()];
    for (int i = 0; i < used_vertices.size(); i++)
        visited[i] = false;

    for (int i = 0; i < used_vertices.size(); i++)
        if (visited[i] == false)
        {
            topologicalSortUtil(i, visited, Stack);
        }
        else
        {
            std::cout << "There is a cycle in current graph!" << std::endl;
            return;
        }
    while (Stack.empty() == false) {
        cout << index_to_id[Stack.top()] << " ";
        Stack.pop();
    }
    cout << endl;
    
    delete[] visited;
}