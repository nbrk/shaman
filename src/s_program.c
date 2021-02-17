/*
 * Copyright 2021 Nikolay Burkov <nbrk@linklevel.net>
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

#include "shaman_internal.h"

#include <assert.h>

#include <GL/glew.h>

static int shamanProgramAddShader(GLuint program,
                                  GLenum shader_type,
                                  const char* shader_src) {
  GLuint shader = glCreateShader(shader_type);
  const GLchar* source[1] = {shader_src};
  const GLint length[1] = {(GLint)strlen(shader_src)};

  glShaderSource(shader, 1, source, length);
  glCompileShader(shader);

  GLint param_val;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &param_val);
  if (param_val != GL_TRUE) {
    // fetch and print the info log
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param_val);
    GLchar* buffer = malloc((size_t)param_val);
    glGetShaderInfoLog(shader, param_val, NULL, buffer);
    glDeleteShader(shader);
    fprintf(stderr, "ERROR: Shader type %d compile error: %s\n", shader_type,
            buffer);
    free(buffer);
    return -1;
  }
  glAttachShader(program, shader);
  glDeleteShader(shader);  // marks the shader for deletion upon deletion of the
                           // program object
  return 0;
}

static GLuint shamanProgramCreate(const char* vertexText,
                                  const char* fragmentText,
                                  const char* geometryText) {
  GLuint program;
  program = glCreateProgram();

  if (shamanProgramAddShader(program, GL_VERTEX_SHADER, vertexText) != 0) {
    glDeleteProgram(program);
    return 0;
  }
  if (shamanProgramAddShader(program, GL_FRAGMENT_SHADER, fragmentText) != 0) {
    glDeleteProgram(program);
    return 0;
  }
  if (geometryText != NULL) {
    if (shamanProgramAddShader(program, GL_GEOMETRY_SHADER, geometryText) !=
        0) {
      glDeleteProgram(program);
      return 0;
    }
  }
  GLint param_val;
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &param_val);
  if (param_val != GL_TRUE) {
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &param_val);
    GLchar* buffer = malloc((size_t)param_val);
    glGetProgramInfoLog(program, param_val, NULL, buffer);
    glDeleteProgram(program);
    fprintf(stderr, "ERROR: Program link error: %s\n", buffer);
    free(buffer);
    return 0;
  }
  glValidateProgram(program);
  glGetProgramiv(program, GL_VALIDATE_STATUS, &param_val);
  if (param_val != GL_TRUE) {
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &param_val);
    GLchar* buffer = malloc((size_t)param_val);
    glGetProgramInfoLog(program, param_val, NULL, buffer);
    glDeleteProgram(program);
    fprintf(stderr, "ERROR: Program validation error: %s\n", buffer);
    free(buffer);
    return 0;
  }

  return program;
}

unsigned shamanMakeProgramFromStrings(const char* vertexText,
                                      const char* fragmentText,
                                      const char* geometryText) {
  assert(vertexText != NULL);
  assert(fragmentText != NULL);
  GLuint program = shamanProgramCreate(vertexText, fragmentText, geometryText);

  if (shamanAbortOnCompileErrors == true) {
    assert(program != 0);
  }

  return (unsigned)program;
}

unsigned shamanMakeProgram(const char* vertexPath,
                           const char* fragmentPath,
                           const char* geometryPath) {
  FILE* fp;

  char* vertexText = NULL;
  char* fragmentText = NULL;
  char* geometryText = NULL;

  assert(vertexPath != NULL);
  assert(fragmentPath != NULL);

  fp = fopen(vertexPath, "r");
  assert(fp != NULL);
  vertexText = shamanFileGetContents(fp);
  fclose(fp);

  fp = fopen(fragmentPath, "r");
  assert(fp != NULL);
  fragmentText = shamanFileGetContents(fp);
  fclose(fp);

  if (geometryPath != NULL) {
    fp = fopen(geometryPath, "r");
    assert(fp != NULL);
    geometryText = shamanFileGetContents(fp);
    fclose(fp);
  }

  GLuint program =
      shamanMakeProgramFromStrings(vertexText, fragmentText, geometryText);

  free(vertexText);
  free(fragmentText);
  free(geometryText);

  if (shamanAbortOnCompileErrors == true) {
    assert(program != 0);
  }

  return (unsigned)program;
}

void shamanDeleteProgram(unsigned program) {
  glDeleteProgram((GLuint)program);
}

void shamanUseProgram(unsigned program) {
  glUseProgram(program);
}

void shamanUnuseProgram(void) {
  glUseProgram(0);
}
