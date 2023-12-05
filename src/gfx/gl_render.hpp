#pragma once

#include "glad/glad.h"
#include "base/math.hpp"

#include "../common.hpp"

typedef struct R_Vertex R_Vertex;
struct R_Vertex
{
  f32 position[3];
  f32 color[3];
};

typedef struct R_Shader R_Shader;
struct R_Shader
{
  u32 id;
};

typedef struct R_VAO R_VAO;
struct R_VAO
{
  u32 id;
  u8 attrib_count;
  u8 attrib_index;
};

// @Error ======================================================================================

#define DEBUG

#ifdef DEBUG
#define GL_ASSERT(call) \
  _gl_clear_error(); \
  call; \
  assert(!_gl_check_error())
#else
#define GL_ASSERT(call) \
  call;
#endif

bool _gl_check_error();
void _gl_clear_error();

// @Buffer =====================================================================================

u32 gl_create_vertex_buffer(void *data, u32 size);
u32 gl_create_vertex_buffer(u32 size);
void gl_bind_vertex_buffer(u32 id);
void gl_unbind_vertex_buffer();
u32 gl_create_index_buffer(void *data, u32 size);
void gl_bind_index_buffer(u32 id);
void gl_unbind_index_buffer();
void gl_generate_vertex_data(R_Vertex *buffer, Vec3F pos, Vec3F color);

// @VAO ========================================================================================

R_VAO gl_create_vertex_array(u8 attrib_count);
void gl_bind_vertex_array(R_VAO *vao);
void gl_unbind_vertex_array();
void gl_add_vertex_attribute(R_VAO *vao, GLenum data_type, u32 count);

// @Shader =====================================================================================

R_Shader gl_create_shader(const i8 *vert_src, const i8 *frag_src);
void gl_bind_shader(R_Shader *shader);
void gl_unbind_shader();
i32 gl_set_uniform_1u(R_Shader *shader, i8 *name, u32 val);
i32 gl_set_uniform_1i(R_Shader *shader, i8 *name, i32 val);
i32 gl_set_uniform_1f(R_Shader *shader, i8 *name, f32 val);
i32 gl_set_uniform_2f(R_Shader *shader, i8 *name, Vec2F vec);
i32 gl_set_uniform_3f(R_Shader *shader, i8 *name, Vec3F vec);
i32 gl_set_uniform_4f(R_Shader *shader, i8 *name, Vec4F vec);
i32 gl_set_uniform_3x3f(R_Shader *shader, i8 *name, Mat3x3F mat);
i32 gl_set_uniform_4x4f(R_Shader *shader, i8 *name, Mat4x4F mat);

// @Draw =======================================================================================
void gl_clear_screen(Vec4F color);
void gl_draw_triangles(u32 vertex_count);
// https://learnopengl.com/Advanced-OpenGL/Instancing
void gl_draw_triangles_instanced(u32 vertex_count);
void gl_draw_lines();
void gl_draw_lines_instanced();
