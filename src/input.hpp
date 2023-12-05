#pragma once

#include "common.hpp"

typedef union SDL_Event SDL_Event;

enum Key
{
  KEY_A,
  KEY_D,
  KEY_S,
  KEY_W,
  KEY_SPACE,
  KEY_ESCAPE,
  KEY_ENTER,
  KEY_BACKSPACE,
  _KEY_COUNT,
};

struct Input
{
  u8 key_down[_KEY_COUNT];
  u8 key_just_down[_KEY_COUNT];
  u8 key_just_up[_KEY_COUNT];
};

bool is_key_pressed(Key key);
bool is_key_just_pressed(Key key);
bool is_key_just_released(Key key);
void clear_last_frame_input(void);
void handle_input(SDL_Event *event, bool *should_close);
