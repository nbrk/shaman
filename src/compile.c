/*
 * Copyright 2020 Nikolay Burkov <nbrk@linklevel.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <shaman.h>

#include <GL/glew.h>

#include <stdlib.h>
#include <string.h>

/**
 * @brief Create and compile shader from the text source
 * @param type
 * @param source
 * @param infolog [out] if error dups infolog here
 * @return opengl shader id or 0 on error
 */
static GLuint compile_shader(GLenum type, const char *source, char **infolog) {
  GLuint id = glCreateShader(type);
  GLint status;
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE && infolog != NULL) {
    // error; read info log
    GLint loglen;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &loglen);
    char *logbuff = malloc(loglen);
    glGetShaderInfoLog(id, loglen, &loglen, logbuff);
    logbuff[loglen - 1] = '\n';
    *infolog = strndup(logbuff, loglen);
    free(logbuff);
    glDeleteShader(id);
    return 0;
  } else {
    return id;
  }
}

shaman_compiled_t shaman_gl_compile(shaman_sources_t sources) {
  shaman_compiled_t compiled;

  compiled.vertex_error = NULL;
  compiled.fragment_error = NULL;

  compiled.vertex_id = compile_shader(GL_VERTEX_SHADER, sources.vertex_text,
                                      &compiled.vertex_error);
  compiled.fragment_id = compile_shader(
      GL_FRAGMENT_SHADER, sources.fragment_text, &compiled.fragment_error);

  return compiled;
}

extern unsigned int shaman_gl_assemble_program(shaman_compiled_t compiled,
                                               char **infolog) {

  GLuint id = glCreateProgram();
  glAttachShader(id, compiled.vertex_id);
  glAttachShader(id, compiled.fragment_id);
  glLinkProgram(id);
  glDetachShader(id, compiled.vertex_id);
  glDetachShader(id, compiled.fragment_id);
  //  glDeleteShader(vertid);
  //  glDeleteShader(fragid);

  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status != GL_TRUE && *infolog != NULL) {
    // read info log
    GLint loglen;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &loglen);
    char *logbuff = malloc(loglen);
    glGetProgramInfoLog(id, loglen, &loglen, logbuff);
    logbuff[loglen - 1] = '\n';
    *infolog = strndup(logbuff, loglen);
    free(logbuff);
    glDeleteProgram(id);
    return 0;
  } else {
    return id;
  }
}

void shaman_gl_delete(shaman_compiled_t compiled) {
  if (compiled.vertex_id != 0)
    glDeleteShader(compiled.vertex_id);
  if (compiled.fragment_id != 0)
    glDeleteShader(compiled.fragment_id);

  if (compiled.vertex_error != NULL)
    free(compiled.vertex_error);
  if (compiled.fragment_error != NULL)
    free(compiled.fragment_error);
}

int shaman_compiled_ok(shaman_compiled_t compiled) {
  if (compiled.vertex_id != 0 && compiled.fragment_id != 0)
    return 0;
  else
    return 1;
}

unsigned int
shaman_gl_read_distinct_compile_assemble_delete(const char *vertex_path,
                                                const char *fragment_path) {
  shaman_sources_t sources = shaman_read_distinct(vertex_path, fragment_path);
  shaman_compiled_t compiled = shaman_gl_compile(sources);
  unsigned int program_id = shaman_gl_assemble_program(compiled, NULL);
  /* XXX */
  glDeleteShader(compiled.vertex_id);
  glDeleteShader(compiled.fragment_id);
  return program_id;
}

unsigned int shaman_gl_read_combined_compile_assemble_delete(const char *path) {
  shaman_sources_t sources = shaman_read_combined(path);
  shaman_compiled_t compiled = shaman_gl_compile(sources);
  return shaman_gl_assemble_program(compiled, NULL);
}
