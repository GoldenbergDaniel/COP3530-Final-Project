#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#include "base/math.hpp"
#include "common.hpp"
#include "state.hpp"
#include "graph.hpp"

#define INF 0xffffff

extern Global *GLOBAL;

static City parse_csv_line(const std::string& line);
static i32 to_x(f32 lon);
static i32 to_y(f32 lat);
static i32 dist(i32 x1, i32 y1, i32 x2, i32 y2);

void read_city_data(City *cities, const char *path)
{
  std::ifstream file(path);
  std::string line;
  std::getline(file, line); // skip the header line

  for (u32 i = 0; std::getline(file, line); i++)
  {
    City city = parse_csv_line(line);
    city.x = to_x(city.longitude);
    city.y = to_y(city.latitude);
    cities[i] = city;
  }

  file.close();
}

void create_graph(Graph *graph, City *cities)
{
  for (i32 i = 0; i < NODE_COUNT; i++)
  {
    for (i32 j = 0; j < cities[i].adjacent.size(); j++)
    {
      Edge edge = {
        .src = i, 
        .dest = cities[i].adjacent[j],
        .weight = dist(cities[i].x, cities[i].y, cities[cities[i].adjacent[j]].x, cities[cities[i].adjacent[j]].x),
      };

      graph->roads[i] = edge;
    }
  }
}

i32 dijkstra_path(Graph *graph, std::vector<i32> &sp, i32 src, i32 end)
{
  u32 numVert = graph->vertex_count;

  std::vector<int> pathID;
  std::priority_queue<std::pair<int, int>, 
    std::vector<std::pair<int, int> >,
    std::greater<std::pair<int, int> > > pq;
  std::vector<std::pair<int, int>> dist(numVert, std::make_pair(INF, INF));

  pq.push(std::make_pair(0, src));
  dist[src] = std::make_pair(0,src);

  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    for (u32 i = 0; i < graph->edge_count; i++)
    {
      int destID = graph->roads[i].dest;
      int weight = graph->roads[i].weight;

      if (dist[destID].first > dist[u].first + weight)
      {
        dist[destID].first = dist[u].first + weight;
        dist[destID].second = u;
        
        pq.push(std::make_pair(dist[destID].first, destID));
      }
    }
  }

  printf("Shortest Path from A to B\n");
  int temp = dist[end].second;
  int distance = dist[end].first;
  sp.push_back(end);
  sp.push_back(temp);

  while (true)
  {
    if (temp == src) break;
    temp = dist[temp].second;
    sp.push_back(temp);
  }
  
  return distance;
}

void bellman_ford_path(Graph *graph, int src, int dest)
{
  int V = graph->vertex_count;
  int E = graph->edge_count;
  std::vector<int> dist(V, INT_MAX);
  std::vector<int> prev(V, -1);
  dist[src] = 0;

  printf("a\n");

  for (int i = 1; i <= V - 1; i++)
  {
    for (int j = 0; j < E; j++)
    {
      int u = graph->roads[j].src;
      int v = graph->roads[j].dest;
      int weight = graph->roads[j].weight;

      printf("%i\n", u);


      if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
      {
        dist[v] = dist[u] + weight;
        prev[v] = u;
      }
    }
  }

  printf("c\n");

  for (int i = 0; i < E; i++)
  {
    int u = graph->roads[i].src;
    int v = graph->roads[i].dest;
    int weight = graph->roads[i].weight;

    if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
    {
      std::cout << "Graph contains negative weight cycle\n";
      return;
    }
  }

  std::cout << "The distance from " << src << " to " << dest << " is:\n";
  std::cout << dist[dest] << "\n" << "And the nodes traveled are:\n";
  int i = dest;
  std::vector<int> path;

  while (i != -1)
  {
    path.push_back(i);
    i = prev[i];
  }

  for (int k = path.size() - 1; k >= 0; k--)
  {
    std::cout << path[k] << " ";
  }

  std::cout << "\n";
}

static 
City parse_csv_line(const std::string& line)
{
  City city;
  std::istringstream ss(line);
  char comma;
  ss >> city.id >> comma >> city.population >> comma >> city.longitude >> comma >> city.latitude >> comma >> city.area >> comma;

  int adjacent_id;
  while (ss >> adjacent_id >> comma)
  {
    city.adjacent.push_back(adjacent_id);
  }

  return city;
}

static i32 to_x(f32 lon)
{
  return 3958 * lon;
}

static i32 to_y(f32 lat)
{
  return 3958 * log(tan(PI/4.0f + lat/2.0f));
}

static i32 dist(i32 x1, i32 y1, i32 x2, i32 y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
