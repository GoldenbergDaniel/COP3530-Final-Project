#include <SDL2/SDL.h>

#include "glad/glad.h"
#include "base/arena.hpp"

#include "../common.hpp"
#include "../state.hpp"
#include "gl_render.hpp"
#include "shaders.h"
#include "draw.hpp"

typedef D_Renderer Renderer;
typedef D_RenderState RenderState;

typedef R_Vertex Vertex;
typedef R_Shader Shader;
typedef R_VAO VAO;

extern Global *GLOBAL;

// Renderer ====================================================================================

Renderer d_create_renderer(void)
{
  Renderer renderer = {0};

  SCOPE("Triangle")
  {
    Vertex vertices[3] = 
    {
      {{-10.0f,  10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // top left
      {{ 20.0f,  0.0f,  1.0f},  {0.0f, 0.0f, 0.0f}}, // right
      {{-10.0f, -10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}  // bottom left
    };

    u32 indices[3] = 
    {
      0, 1, 2
    };

    VAO vao = gl_create_vertex_array(2);
    u32 vbo = gl_create_vertex_buffer(&vertices, sizeof (vertices));
    u32 ibo = gl_create_index_buffer(&indices, sizeof (indices));
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // position
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // color

    renderer.triangle.vao = vao;
    renderer.triangle.vbo = vbo;
    renderer.triangle.ibo = ibo;

    Shader shader = gl_create_shader(primitive_vert_src, primitive_frag_src);
    renderer.triangle.shader = shader;

    gl_unbind_vertex_array();
  }

  SCOPE("Rectangle")
  {
    Vertex vertices[4] = 
    {
      {{-10.0f,  10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // top left
      {{ 10.0f,  10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // top right
      {{ 10.0f, -10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // bottom right
      {{-10.0f, -10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}  // bottom left
    };

    u32 indices[6] = 
    {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
    };

    VAO vao = gl_create_vertex_array(2);
    u32 vbo = gl_create_vertex_buffer(&vertices, sizeof (vertices));
    u32 ibo = gl_create_index_buffer(&indices, sizeof (indices));
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // position
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // color

    renderer.rectangle.vao = vao;
    renderer.rectangle.vbo = vbo;
    renderer.rectangle.ibo = ibo;

    Shader shader = gl_create_shader(primitive_vert_src, primitive_frag_src);
    renderer.rectangle.shader = shader;

    gl_unbind_vertex_array();
  }

  SCOPE("Line")
  {
    Vertex vertices[2] = 
    {
      {{-10.0f,  10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // left
      {{ 10.0f,  10.0f, 1.0f},  {0.0f, 0.0f, 0.0f}}, // right
    };

    VAO vao = gl_create_vertex_array(2);
    u32 vbo = gl_create_vertex_buffer(&vertices, sizeof (vertices));
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // position
    gl_add_vertex_attribute(&vao, GL_FLOAT, 3); // color

    renderer.line.vao = vao;
    renderer.line.vbo = vbo;

    Shader shader = gl_create_shader(primitive_vert_src, primitive_frag_src);
    renderer.line.shader = shader;

    gl_unbind_vertex_array();
  }

  return renderer;
}

void d_clear(Vec4F color)
{
  gl_clear_screen(color);
}

void d_triangle(Mat3x3F xform, Vec4F color)
{
  RenderState state = GLOBAL->renderer.triangle;

  gl_bind_shader(&state.shader);
  gl_set_uniform_3x3f(&state.shader, (char *) "u_xform", xform);
  gl_set_uniform_4f(&state.shader, (char *) "u_color", color);

  gl_bind_vertex_array(&state.vao);
  gl_draw_triangles(3);
  
  gl_unbind_vertex_array();
}

void d_rectangle(Mat3x3F xform, Vec4F color)
{
  RenderState state = GLOBAL->renderer.rectangle;

  gl_bind_shader(&state.shader);
  gl_set_uniform_3x3f(&state.shader, (char *) "u_xform", xform);
  gl_set_uniform_4f(&state.shader, (char *) "u_color", color);

  gl_bind_vertex_array(&state.vao);
  gl_draw_triangles(6);

  gl_unbind_vertex_array();
}

void d_rectangle_efficient(Mat3x3F xform, Vec4F color)
{
  RenderState state = GLOBAL->renderer.rectangle;

  gl_bind_shader(&state.shader);
  gl_set_uniform_3x3f(&state.shader, (char *) "u_xform", xform);
  gl_set_uniform_4f(&state.shader, (char *) "u_color", color);

  gl_bind_vertex_array(&state.vao);
  gl_draw_triangles(6);

  gl_unbind_vertex_array();
}

// void d_line(Vec2F p0, Vec2F p1, Vec4F color)
// {
//   D_Renderer renderer = GLOBAL->renderer.line;

//   SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
// }
