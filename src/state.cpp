#include <stdio.h>

#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

#include "common.hpp"
#include "graph.hpp"
#include "state.hpp"
#include "gfx/draw.hpp"

extern Global *GLOBAL;

void init(State *state)
{
  state->xform = m3x3f(1.0f);
  state->xform = translate_3x3f(W_WIDTH/2.0f, W_HEIGHT/2.0f) * state->xform;
  state->xform = orthographic_3x3f(0.0f, W_WIDTH, 0.0f, W_HEIGHT) * state->xform;
}

void update(State *state)
{
  ImGui::Begin("Dijkestra");
  ImGui::SetWindowSize(ImVec2(500, 300));
  ImGui::Text("Enter your starting city");
  ImGui::InputInt("FROM ID", &state->from_id_input1, 0, 99999);
  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  ImGui::Text("Enter your destination city");
  ImGui::InputInt("TO ID", &state->to_id_input1, 0, 99999);
  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  if (ImGui::Button("Find Route"))
  {
    std::vector<i32> sp;
    dijkstra_path(&state->graph, sp, state->from_id_input1, state->to_id_input1);
    printf("hmm?\n");
    for (u32 i = 0; i < sp.size(); i++)
    {
      std::cout << sp[i] << ",";
    }
    printf("\n");
  }
  ImGui::End();

  ImGui::Begin("Bellman-Ford");
  ImGui::SetWindowSize(ImVec2(500, 300));
  ImGui::Text("Enter your starting city");
  ImGui::InputInt("FROM ID", &state->from_id_input2, 0, 99999);
  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  ImGui::Text("Enter your destination city");
  ImGui::InputInt("TO ID", &state->to_id_input2, 0, 99999);
  ImGui::Dummy(ImVec2(0.0f, 20.0f));
  if (ImGui::Button("Find Route"))
  {
    bellman_ford_path(&state->graph, state->from_id_input2, state->to_id_input2);
    printf("some?\n");
  }
  ImGui::End();
}

void draw(State *state)
{
  d_clear(v4f(0.3f, 0.3f, 0.5f, 1.0f));

  for (u32 i = 0; i < 10000; i++)
  {
    d_rectangle(state->xform, v4f(1, 1, 1, 1));
  }
}

bool should_quit(State *state)
{
  bool result = false;
  
  if (state->should_quit || is_key_pressed(KEY_ESCAPE))
  {
    result = true;
  }

  return result;
}

//d_line(v2f((W_WIDTH/2.0f)-10, W_HEIGHT/2.0f), v2f((W_WIDTH/2.0f)+10, W_HEIGHT/2.0f), v4f(1, 0, 0, 1));
