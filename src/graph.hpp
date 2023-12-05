#pragma once

#include <iostream>
#include <vector>

#include "common.hpp"

struct City
{
  i32 id;
  f32 latitude;
  f32 longitude;
  i32 x;
  i32 y;
  i32 population;
  f32 area;
  std::vector<i32> adjacent;
};

struct Edge
{
  i32 src;
  i32 dest;
  i32 weight;
};

struct Graph
{
  u32 vertex_count;
  u32 edge_count;
  Edge roads[NODE_COUNT*3] = {};
};

void read_city_data(City *cities, const char *path);
i32 dijkstra_path(Graph *graph, std::vector<i32> &sp, i32 src, i32 end);
void bellman_ford_path(Graph *graph, int src, int dest);
