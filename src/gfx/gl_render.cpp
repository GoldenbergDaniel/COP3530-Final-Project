#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "base/math.hpp"

#include "../common.hpp"
#include "gl_render.hpp"

typedef R_Shader Shader;
typedef GL_VAO VAO;

static void gl_verify_shader(u32 id, u32 type);

bool _gl_check_error(void)
{
  bool result = false;

  for (u32 err = -1; (err = glGetError());)
  {
    printf("[OpenGL Error]: %u\n", err);
    result = true;
  }

  return result;
}

void _gl_clear_error(void)
{
  while (glGetError() != GL_NO_ERROR);
}

// @Buffer =====================================================================================

u32 gl_create_vertex_buffer(void *data, u32 size)
{
  u32 id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

  return id;
}

inline
void gl_bind_vertex_buffer(u32 id)
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

inline
void gl_unbind_vertex_buffer(void)
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

u32 gl_create_index_buffer(void *data, u32 size)
{
  u32 id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

  return id;
}

inline
void gl_bind_index_buffer(u32 id)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

inline
void gl_unbind_index_buffer(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// @VAO ========================================================================================

VAO gl_create_vertex_array(u8 attrib_count)
{
  u32 id;
  GL_ASSERT(glGenVertexArrays(1, &id));
  GL_ASSERT(glBindVertexArray(id));

  return (VAO) {id, attrib_count, 0};
}

inline
void gl_bind_vertex_array(VAO *vao)
{
  GL_ASSERT(glBindVertexArray(vao->id));
}

inline
void gl_unbind_vertex_array(void)
{
  glBindVertexArray(0);
}

void gl_set_vertex_attribute(VAO *vao, GLenum data_type, u32 count)
{
  typedef struct Layout Layout;
  struct Layout
  {
    u32 index;
    u32 count;
    u32 data_type;
    bool normalized;
    u32 stride;
    void *offset;
  };

  u8 type_size;
  switch (data_type)
  {
    case GL_BYTE:  type_size = sizeof (i8);  break;
    case GL_SHORT: type_size = sizeof (i16); break;
    case GL_INT:   type_size = sizeof (i32); break;
    case GL_FLOAT: type_size = sizeof (f32); break;
    default: ASSERT(false);
  }

  Layout layout = 
  {
    .index = vao->attrib_index,
    .count = count,
    .data_type = data_type,
    .normalized = false,
    .stride = count * vao->attrib_count * type_size,
    .offset = (void *) (u64) (vao->attrib_index * count * type_size)
  };

  vao->attrib_index++;

  GL_ASSERT(glVertexAttribPointer(
                                  layout.index,
                                  layout.count,
                                  layout.data_type,
                                  layout.normalized,
                                  layout.stride,
                                  layout.offset));

  GL_ASSERT(glEnableVertexAttribArray(layout.index));
}

// @Shader =====================================================================================

Shader gl_create_shader(const i8 *vert_src, const i8 *frag_src)
{
  u32 vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vert_src, nullptr);
  glCompileShader(vert);

  u32 frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &frag_src, nullptr);
  glCompileShader(frag);

  #ifdef DEBUG
  gl_verify_shader(vert, GL_COMPILE_STATUS);
  gl_verify_shader(frag, GL_COMPILE_STATUS);
  #endif

  u32 id = glCreateProgram();
  glAttachShader(id, frag);
  glAttachShader(id, vert);
  glLinkProgram(id);

  #ifdef DEBUG
  gl_verify_shader(id, GL_LINK_STATUS);
  #endif

  glDeleteShader(vert);
  glDeleteShader(frag);

  return (Shader) {id};
}

inline
void gl_bind_shader(Shader *shader)
{
  GL_ASSERT(glUseProgram(shader->id));
}

inline
void gl_unbind_shader(void)
{
  glUseProgram(0);
}

i32 gl_set_uniform_1u(Shader *shader, i8 *name, u32 val)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform1ui(loc, val);
  
  return loc;
}

i32 gl_set_uniform_1(Shader *shader, i8 *name, i32 val)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform1i(loc, val);
  return loc;
}

i32 gl_set_uniform_1f(Shader *shader, i8 *name, f32 val)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform1f(loc, val);
  
  return loc;
}

i32 gl_set_uniform_2f(Shader *shader, i8 *name, Vec2F vec)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform2f(loc, vec.x, vec.y);

  return loc;
}

i32 gl_set_uniform_3f(Shader *shader, i8 *name, Vec3F vec)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform3f(loc, vec.x, vec.y, vec.z);
  
  return loc;
}

i32 gl_set_uniform_4f(Shader *shader, i8 *name, Vec4F vec)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
  
  return loc;
}

i32 gl_set_uniform_4x4f(Shader *shader, i8 *name, Mat4x4F mat)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniformMatrix4fv(loc, 1, false, &mat.elements[0][0]);
  
  return loc;
}

i32 gl_set_uniform_3x3f(Shader *shader, i8 *name, Mat3x3F mat)
{
  i32 loc = glGetUniformLocation(shader->id, name);
  glUniformMatrix3fv(loc, 1, false, &mat.elements[0][0]);
  
  return loc;
}

static
void gl_verify_shader(u32 id, u32 type)
{
  i32 success;

  if (type == GL_LINK_STATUS)
  {
    glValidateProgram(id);
  }

  glGetShaderiv(id, type, &success);

  if (!success)
  {
    i32 length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    i8 log[length];
    glGetShaderInfoLog(id, length, &length, log);

    if (type == GL_COMPILE_STATUS)
    {
      printf("[GLObject Error]: Failed to compile shader!\n");
    }
    else
    {
      printf("[GLObject Error]: Failed to link shaders!\n");
    }

    printf("%s", log);
  }
}

// @Draw =======================================================================================

inline
void gl_draw_triangles(u32 vertex_count)
{
  GL_ASSERT(glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, nullptr));
}

inline
void gl_draw_triangles_instanced(u32 vertex_count)
{

}
