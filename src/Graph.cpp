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
    edge_weights[{v, w}] = 1;
}

void Graph::addEdge(int v, int w, float weight)
{
    adj[v].push_back(w);
    edge_weights[{v, w}] = weight;
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

std::vector<int> Graph::dijkstra(int start, int target, std::map<int, int> index_to_id)
{
    if (start < 0 || start >= V || target < 0 || target >= V) {
        return {};
    }

    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> prev(V, -1);
    std::vector<bool> visited(V, false);

    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == target) {
            break;
        }

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (int v : adj[u]) {
            int weight = edge_weights[{u, v}];

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> path;
    if (dist[target] == std::numeric_limits<int>::max()) {
        return path;
    }

    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return path;
}