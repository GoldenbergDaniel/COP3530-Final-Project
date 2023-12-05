#include <iostream>
#include <SDL2/SDL.h>

#include "base/arena.hpp"
#include "glad/glad.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

#include "common.hpp"
#include "state.hpp"
#include "input.hpp"

#define TARGET_FPS 60

#define VSYNC_AUTO -1
#define VSYNC_OFF 0
#define VSYNC_ON 1

Global *GLOBAL;

i32 main(void)
{
  State state = {};
  state.perm_arena = Arena(MiB(64));
  state.graph = {.vertex_count = 1000, .edge_count = 3000};
  state.city_count = 1000;
  state.cities = (City *) state.perm_arena.alloc(sizeof (City) * state.city_count);
  read_city_data(state.cities, "cities.csv");

  SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  SDL_Window *window = SDL_CreateWindow(
                                        "TRAVELLER",
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        W_WIDTH, 
                                        W_HEIGHT, 
                                        W_FLAGS);

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(VSYNC_ON);

  if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
  {
    printf("GLAD failed to load!\n");
    return 1;
  }

  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
  ImGui_ImplOpenGL3_Init("#version 410");

  init(&state);

  GLOBAL = (Global *) state.perm_arena.alloc(sizeof (Global));
  GLOBAL->renderer = d_create_renderer();

  f64 elapsed_time = 0.0f;
  f64 current_time = SDL_GetTicks64() * 0.001f;
  f64 time_step = 1.0f / TARGET_FPS;
  f64 accumulator = 0.0f;

  bool running = true;
  while (running)
  {
    f64 new_time = SDL_GetTicks64() * 0.001f;
    f64 frame_time = new_time - current_time;
    current_time = new_time;
    accumulator += frame_time;

    while (accumulator >= time_step)
    {
      clear_last_frame_input();

      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
        ImGui_ImplSDL2_ProcessEvent(&event);
        handle_input(&event, &state.should_quit);
      }

      if (should_quit(&state))
      {
        running = false;
        break;
      }

      if (elapsed_time > 0.1f)
      {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();

        update(&state);
        draw(&state);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
      }

      elapsed_time += time_step;
      accumulator -= time_step;
    }
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
