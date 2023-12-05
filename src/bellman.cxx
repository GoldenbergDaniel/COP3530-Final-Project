#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
  int src, dest, weight;
};

struct Graph
{
  int V, E;
  vector<Edge> edges;
};

void bellman_ford(Graph graph, int src, int dest)
{
  int V = graph.V;
  int E = graph.E;
  vector<int> dist(V, INT_MAX);
  vector<int> prev(V, -1);
  dist[src] = 0;

  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = graph.edges[j].src;
      int v = graph.edges[j].dest;
      int weight = graph.edges[j].weight;
      if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        prev[v] = u;
      }
    }
  }

  for (int i = 0; i < E; i++) {
    int u = graph.edges[i].src;
    int v = graph.edges[i].dest;
    int weight = graph.edges[i].weight;
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
      cout << "Graph contains negative weight cycle" << endl;
      return;
    }
  }

  cout << "The distance from " << src << " to " << dest << " is:" << endl;
  cout << dist[dest] << endl << "And the nodes traveled are:" << endl;
  int i = dest;
  vector<int> path;
  while (i != -1) {
    path.push_back(i);
    i = prev[i];
  }
  for (int k = path.size() - 1; k >= 0; k--) {
    cout << path[k] << " ";
  }
  cout << endl;
}

int main() {
  Graph graph = { 5, 8, {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}} };
  bellman_ford(graph, 0, 3);
  return 0;
}
