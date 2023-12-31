/*
  Arena Allocator
  Written by Daniel Goldenberg
*/

#include "../src/common.hpp"
#include "arena.hpp"

Arena::Arena()
{
  this->memory = new byte[MiB(4)];
  this->size = MiB(4);
  this->used = 0;
}

Arena::Arena(u64 size)
{
  this->memory = new byte[size];
  this->size = size;
  this->used = 0;
}

Arena::~Arena()
{
  delete[] this->memory;
  this->memory = nullptr;
  this->size = 0;
  this->used = 0;
}

void *Arena::alloc(u64 size)
{
  assert(this->size >= this->used + size);

  byte *allocated = this->memory + this->used;
  this->used += size;

  return allocated;
}

void Arena::free(u64 size)
{
  assert(this->used - size >= 0);

  this->used -= size;
}

void Arena::clear()
{
  this->used = 0;
}
