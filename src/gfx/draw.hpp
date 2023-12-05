#pragma once

#include "base/arena.hpp"
#include "base/math.hpp"

#include "gl_render.hpp"
#include "../common.hpp"

typedef struct D_Renderer D_Renderer;
typedef struct D_RenderState D_RenderState;

struct D_RenderState
{
  R_Shader shader;
  R_VAO vao;
  u32 vbo;
  u32 ibo;
};

struct D_Renderer
{
  D_RenderState triangle;
  D_RenderState rectangle;
  D_RenderState line;
};

#define R_MAX_VERTICES_PER_BATCH 20000
#define R_MAX_INDICES_PER_BATCH 30000

// Renderer ====================================================================================

D_Renderer d_create_renderer(void);
void d_clear(Vec4F color);
void d_rectangle(Mat3x3F xform, Vec4F color);
void d_rectangle_efficient(Mat3x3F xform, Vec4F color);
void d_line(Vec2F p0, Vec2F p1, Vec4F color);
