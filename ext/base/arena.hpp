/*
  Arena Allocator
  Written by Daniel Goldenberg
*/

#pragma once

#include "../src/common.hpp"

class Arena
{
private:
  byte *memory;
  u64 size;
public:
  u64 used;

  Arena();
  Arena(u64 size);
  ~Arena();
  void *alloc(u64 size);
  void free(u64 size);
  void clear();
};

#define KiB(bytes) (bytes << 10)
#define MiB(bytes) (bytes << 20)
#define GiB(bytes) (bytes << 30)
