#pragma once

#include "base/arena.hpp"

#include "input.hpp"
#include "graph.hpp"
#include "gfx/draw.hpp"

typedef struct SDL_Renderer SDL_Renderer;

struct State
{
  Arena perm_arena;
  City *cities;
  u32 city_count;
  Graph graph;
  bool should_quit;

  i32 from_id_input1;
  i32 to_id_input1;
  
  i32 from_id_input2;
  i32 to_id_input2;

  Mat3x3F xform = {};
};

struct Global
{
  Input input;
  D_Renderer renderer;
};

#define W_NAME "TRAVELLER"
#define W_WIDTH 1200
#define W_HEIGHT 675
#define W_FLAGS SDL_WINDOW_OPENGL

void init(State *state);
void update(State *state);
void draw(State *state);
bool should_quit(State *state);
