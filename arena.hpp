#pragma once

#include "common.hpp"

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

#define KILOBYTES(bytes) (bytes << 10)
#define MEGABYTES(bytes) (bytes << 20)
#define GIGABYTES(bytes) (bytes << 30)
