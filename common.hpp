#pragma once

#include <assert.h>

typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef float f32;
typedef double f64;

#define ASSERT(exp) assert(exp)

#define I32_MAX 2147483647
#define I32_MIN -2147483647
