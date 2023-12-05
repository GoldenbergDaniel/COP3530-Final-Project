#include <SDL2/SDL.h>

#include "common.hpp"
#include "state.hpp"
#include "input.hpp"

extern Global *GLOBAL;

bool is_key_pressed(Key key)
{
  return GLOBAL->input.key_down[key];
}

bool is_key_just_pressed(Key key)
{
  return GLOBAL->input.key_just_down[key];
}

bool is_key_just_released(Key key)
{
  return GLOBAL->input.key_just_up[key];
}

void clear_last_frame_input(void)
{
  for (u8 i = 0; i < sizeof (GLOBAL->input.key_just_down); i++)
  {
    GLOBAL->input.key_just_down[i] = false;
    GLOBAL->input.key_just_up[i] = false;
  }
}

void handle_input(SDL_Event *event, bool *should_quit)
{
  Input *input = &GLOBAL->input;

  switch (event->type)
  {
    case SDL_QUIT: *should_quit = true;
    break;
    case SDL_KEYDOWN: 
    {
      switch (event->key.keysym.scancode)
      {
        default: break;
        case SDL_SCANCODE_A:
        {
          if (!input->key_down[KEY_A])
            input->key_just_down[KEY_A] = true;

          input->key_down[KEY_A] = true;
        }
        break;
        case SDL_SCANCODE_D:
        {
          if (!input->key_down[KEY_D])
            input->key_just_down[KEY_D] = true;

          input->key_down[KEY_D] = true;
        }
        break;
        case SDL_SCANCODE_S:
        {
          if (!input->key_down[KEY_S])
            input->key_just_down[KEY_S] = true;

          input->key_down[KEY_S] = true;
        }
        break;
        case SDL_SCANCODE_W: 
        {
          if (!input->key_down[KEY_W])
            input->key_just_down[KEY_W] = true;

          input->key_down[KEY_W] = true;
        }
        break;
        case SDL_SCANCODE_ESCAPE:
        {
          if (!input->key_down[KEY_ESCAPE])
            input->key_just_down[KEY_ESCAPE] = true;

          input->key_down[KEY_ESCAPE] = true;
        }
        break;
        case SDL_SCANCODE_SPACE:
        {
          if (!input->key_down[KEY_SPACE])
            input->key_just_down[KEY_SPACE] = true;

          input->key_down[KEY_SPACE] = true;
        }
        break;
        case SDL_SCANCODE_RETURN:
        {
          if (!input->key_down[KEY_ENTER])
            input->key_just_down[KEY_ENTER] = true;

          input->key_down[KEY_ENTER] = true;
        }
        break;
        case SDL_SCANCODE_BACKSPACE:
        {
          if (!input->key_down[KEY_BACKSPACE])
            input->key_just_down[KEY_BACKSPACE] = true;

          input->key_down[KEY_BACKSPACE] = true;
        }
      }
      break;
    }
    case SDL_KEYUP: 
    {
      switch (event->key.keysym.scancode)
      {
        default: break;
        case SDL_SCANCODE_A:
        {
          if (input->key_down[KEY_A])
            input->key_just_up[KEY_A] = true;

          input->key_down[KEY_A] = false;
        }
        break;
        case SDL_SCANCODE_D:
        {
          if (input->key_down[KEY_D])
            input->key_just_up[KEY_D] = true;

          input->key_down[KEY_D] = false;
        }
        break;
        case SDL_SCANCODE_S:
        {
          if (input->key_down[KEY_S])
            input->key_just_up[KEY_S] = true;

          input->key_down[KEY_S] = false;
        }
        break;
        case SDL_SCANCODE_W: 
        {
          if (input->key_down[KEY_W])
            input->key_just_up[KEY_W] = true;

          input->key_down[KEY_W] = false;
        }
        break;
        case SDL_SCANCODE_ESCAPE:
        {
          if (input->key_down[KEY_ESCAPE])
            input->key_just_up[KEY_ESCAPE] = true;

          input->key_down[KEY_ESCAPE] = false;
        }
        break;
        case SDL_SCANCODE_SPACE:
        {
          if (input->key_down[KEY_SPACE])
            input->key_just_up[KEY_SPACE] = true;

          input->key_down[KEY_SPACE] = false;
        }
        break;
        case SDL_SCANCODE_RETURN:
        {
          if (input->key_down[KEY_ENTER])
            input->key_just_up[KEY_ENTER] = true;

          input->key_down[KEY_ENTER] = false;
        }
        break;
        case SDL_SCANCODE_BACKSPACE:
        {
          if (input->key_down[KEY_ENTER])
            input->key_just_up[KEY_ENTER] = true;

          input->key_down[KEY_ENTER] = false;
        }
      }
      break;
    }
  }
}
