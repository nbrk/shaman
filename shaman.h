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
#pragma once

#include <stdbool.h>

/*
 * Simple OpenGL shader management library (shaman).
 *
 */

/*
 * DATA.
 */
extern bool shamanWarnOnMissingAttribLocation;
extern bool shamanWarnOnMissingUniformLocation;
extern bool shamanAbortOnCompileErrors;
extern bool shamanAbortOnMissingAttribLocation;
extern bool shamanAbortOnMissingUniformLocation;

/*
 * FUNCTIONS.
 */
extern unsigned shamanMakeProgram(const char* vertexShaderPath,
                                  const char* fragmentShaderPath,
                                  const char* geometryShaderPath);

extern unsigned shamanMakeProgramFromStrings(const char* vertexShaderText,
                                             const char* fragmentShaderText,
                                             const char* geometryShaderText);

extern void shamanUseProgram(unsigned program);

extern void shamanUnuseProgram(void);

extern void shamanDeleteProgram(unsigned program);

extern int shamanGetAttribLocation(unsigned program, const char* name);

extern int shamanGetUniformLocation(unsigned program, const char* name);

/*
 * Uniforms values via stack
 */
extern void shamanSetUniform1f(unsigned program, const char* name, float v0);
extern void shamanSetUniform2f(unsigned program,
                               const char* name,
                               float v0,
                               float v1);
extern void shamanSetUniform3f(unsigned program,
                               const char* name,
                               float v0,
                               float v1,
                               float v2);
extern void shamanSetUniform4f(unsigned program,
                               const char* name,
                               float v0,
                               float v1,
                               float v2,
                               float v3);

extern void shamanSetUniform1i(unsigned program, const char* name, int v0);
extern void shamanSetUniform2i(unsigned program,
                               const char* name,
                               int v0,
                               int v1);
extern void shamanSetUniform3i(unsigned program,
                               const char* name,
                               int v0,
                               int v1,
                               int v2);
extern void shamanSetUniform4i(unsigned program,
                               const char* name,
                               int v0,
                               int v1,
                               int v2,
                               int v3);

extern void shamanSetUniform1ui(unsigned program,
                                const char* name,
                                unsigned v0);
extern void shamanSetUniform2ui(unsigned program,
                                const char* name,
                                unsigned v0,
                                unsigned v1);
extern void shamanSetUniform3ui(unsigned program,
                                const char* name,
                                unsigned v0,
                                unsigned v1,
                                unsigned v2);
extern void shamanSetUniform4ui(unsigned program,
                                const char* name,
                                unsigned v0,
                                unsigned v1,
                                unsigned v2,
                                unsigned v3);

/*
 * Uniforms vectorized
 */

extern void shamanSetUniform1fv(unsigned program,
                                const char* name,
                                int count,
                                const float* value);
extern void shamanSetUniform2fv(unsigned program,
                                const char* name,
                                int count,
                                const float* value);
extern void shamanSetUniform3fv(unsigned program,
                                const char* name,
                                int count,
                                const float* value);
extern void shamanSetUniform4fv(unsigned program,
                                const char* name,
                                int count,
                                const float* value);

extern void shamanSetUniform1iv(unsigned program,
                                const char* name,
                                int count,
                                const int* value);
extern void shamanSetUniform2iv(unsigned program,
                                const char* name,
                                int count,
                                const int* value);
extern void shamanSetUniform3iv(unsigned program,
                                const char* name,
                                int count,
                                const int* value);
extern void shamanSetUniform4iv(unsigned program,
                                const char* name,
                                int count,
                                const int* value);

extern void shamanSetUniform1uiv(unsigned program,
                                 const char* name,
                                 int count,
                                 const unsigned* value);
extern void shamanSetUniform2uiv(unsigned program,
                                 const char* name,
                                 int count,
                                 const unsigned* value);
extern void shamanSetUniform3uiv(unsigned program,
                                 const char* name,
                                 int count,
                                 const unsigned* value);
extern void shamanSetUniform4uiv(unsigned program,
                                 const char* name,
                                 int count,
                                 const unsigned* value);

/*
 * Uniforms matrices
 */

extern void shamanSetUniformMatrix2fv(unsigned program,
                                      const char* name,
                                      int count,
                                      bool transpose,
                                      const float* value);
extern void shamanSetUniformMatrix3fv(unsigned program,
                                      const char* name,
                                      int count,
                                      bool transpose,
                                      const float* value);
extern void shamanSetUniformMatrix4fv(unsigned program,
                                      const char* name,
                                      int count,
                                      bool transpose,
                                      const float* value);
extern void shamanSetUniformMatrix2x3fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);
extern void shamanSetUniformMatrix3x2fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);
extern void shamanSetUniformMatrix2x4fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);
extern void shamanSetUniformMatrix4x2fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);
extern void shamanSetUniformMatrix3x4fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);
extern void shamanSetUniformMatrix4x3fv(unsigned program,
                                        const char* name,
                                        int count,
                                        bool transpose,
                                        const float* value);

#ifdef SHAMAN_IMPLEMENTATION
#include <GL/glew.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool shamanWarnOnMissingAttribLocation = true;
bool shamanWarnOnMissingUniformLocation = true;
bool shamanAbortOnCompileErrors = false;
bool shamanAbortOnMissingAttribLocation = true;
bool shamanAbortOnMissingUniformLocation = true;

size_t shamanFileGetSize(FILE* fp) {
  size_t curpos = ftell(fp);
  fseek(fp, 0, SEEK_END);
  size_t endpos = ftell(fp);
  fseek(fp, curpos, SEEK_SET);
  return endpos;
}

char* shamanFileGetContents(FILE* fp) {
  size_t sourcelen = shamanFileGetSize(fp);
  char* source = malloc(sourcelen + 1);
  size_t nobjs = fread(source, sourcelen, 1, fp);

  if (nobjs != 1) {
    free(source);
    return NULL;
  } else
    return source;
}

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

int shamanGetAttribLocation(unsigned program, const char* name) {
  GLint location = glGetAttribLocation(program, name);
  if (location == -1) {
    if (shamanWarnOnMissingAttribLocation)
      fprintf(stderr, "WARNING: No attrib '%s' in shader program %d\n", name,
              program);
    if (shamanAbortOnMissingAttribLocation)
      assert(location != -1);
  }

  return (int)location;
}

int shamanGetUniformLocation(unsigned program, const char* name) {
  GLint location = glGetUniformLocation(program, name);
  if (location == -1) {
    if (shamanWarnOnMissingUniformLocation)
      fprintf(stderr, "WARNING: No uniform '%s' in shader program %d\n", name,
              program);
    if (shamanAbortOnMissingUniformLocation)
      assert(location != -1);
  }

  return (int)location;
}

void shamanSetUniform1f(unsigned program, const char* name, float v0) {
  glUniform1f(shamanGetUniformLocation(program, name), v0);
}
void shamanSetUniform2f(unsigned program,
                        const char* name,
                        float v0,
                        float v1) {
  glUniform2f(shamanGetUniformLocation(program, name), v0, v1);
}
void shamanSetUniform3f(unsigned program,
                        const char* name,
                        float v0,
                        float v1,
                        float v2) {
  glUniform3f(shamanGetUniformLocation(program, name), v0, v1, v2);
}
void shamanSetUniform4f(unsigned program,
                        const char* name,
                        float v0,
                        float v1,
                        float v2,
                        float v3) {
  glUniform4f(shamanGetUniformLocation(program, name), v0, v1, v2, v3);
}

void shamanSetUniform1i(unsigned program, const char* name, int v0) {
  glUniform1i(shamanGetUniformLocation(program, name), v0);
}
void shamanSetUniform2i(unsigned program, const char* name, int v0, int v1) {
  glUniform2i(shamanGetUniformLocation(program, name), v0, v1);
}
void shamanSetUniform3i(unsigned program,
                        const char* name,
                        int v0,
                        int v1,
                        int v2) {
  glUniform3i(shamanGetUniformLocation(program, name), v0, v1, v2);
}
void shamanSetUniform4i(unsigned program,
                        const char* name,
                        int v0,
                        int v1,
                        int v2,
                        int v3) {
  glUniform4i(shamanGetUniformLocation(program, name), v0, v1, v2, v3);
}

void shamanSetUniform1ui(unsigned program, const char* name, unsigned v0) {
  glUniform1ui(shamanGetUniformLocation(program, name), v0);
}
void shamanSetUniform2ui(unsigned program,
                         const char* name,
                         unsigned v0,
                         unsigned v1) {
  glUniform2ui(shamanGetUniformLocation(program, name), v0, v1);
}
void shamanSetUniform3ui(unsigned program,
                         const char* name,
                         unsigned v0,
                         unsigned v1,
                         unsigned v2) {
  glUniform3ui(shamanGetUniformLocation(program, name), v0, v1, v2);
}
void shamanSetUniform4ui(unsigned program,
                         const char* name,
                         unsigned v0,
                         unsigned v1,
                         unsigned v2,
                         unsigned v3) {
  glUniform4ui(shamanGetUniformLocation(program, name), v0, v1, v2, v3);
}

void shamanSetUniform1fv(unsigned program,
                         const char* name,
                         int count,
                         const float* value) {
  glUniform1fv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform2fv(unsigned program,
                         const char* name,
                         int count,
                         const float* value) {
  glUniform2fv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform3fv(unsigned program,
                         const char* name,
                         int count,
                         const float* value) {
  glUniform3fv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform4fv(unsigned program,
                         const char* name,
                         int count,
                         const float* value) {
  glUniform4fv(shamanGetUniformLocation(program, name), count, value);
}

void shamanSetUniform1iv(unsigned program,
                         const char* name,
                         int count,
                         const int* value) {
  glUniform1iv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform2iv(unsigned program,
                         const char* name,
                         int count,
                         const int* value) {
  glUniform2iv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform3iv(unsigned program,
                         const char* name,
                         int count,
                         const int* value) {
  glUniform3iv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform4iv(unsigned program,
                         const char* name,
                         int count,
                         const int* value) {
  glUniform4iv(shamanGetUniformLocation(program, name), count, value);
}

void shamanSetUniform1uiv(unsigned program,
                          const char* name,
                          int count,
                          const unsigned* value) {
  glUniform1uiv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform2uiv(unsigned program,
                          const char* name,
                          int count,
                          const unsigned* value) {
  glUniform2uiv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform3uiv(unsigned program,
                          const char* name,
                          int count,
                          const unsigned* value) {
  glUniform3uiv(shamanGetUniformLocation(program, name), count, value);
}
void shamanSetUniform4uiv(unsigned program,
                          const char* name,
                          int count,
                          const unsigned* value) {
  glUniform4uiv(shamanGetUniformLocation(program, name), count, value);
}

void shamanSetUniformMatrix2fv(unsigned program,
                               const char* name,
                               int count,
                               bool transpose,
                               const float* value) {
  glUniformMatrix2fv(shamanGetUniformLocation(program, name), count, transpose,
                     value);
}
void shamanSetUniformMatrix3fv(unsigned program,
                               const char* name,
                               int count,
                               bool transpose,
                               const float* value) {
  glUniformMatrix3fv(shamanGetUniformLocation(program, name), count, transpose,
                     value);
}
void shamanSetUniformMatrix4fv(unsigned program,
                               const char* name,
                               int count,
                               bool transpose,
                               const float* value) {
  glUniformMatrix4fv(shamanGetUniformLocation(program, name), count, transpose,
                     value);
}

void shamanSetUniformMatrix2x3fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix2x3fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}
void shamanSetUniformMatrix3x2fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix3x2fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}
void shamanSetUniformMatrix2x4fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix2x4fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}
void shamanSetUniformMatrix4x2fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix4x2fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}
void shamanSetUniformMatrix3x4fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix3x4fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}
void shamanSetUniformMatrix4x3fv(unsigned program,
                                 const char* name,
                                 int count,
                                 bool transpose,
                                 const float* value) {
  glUniformMatrix4x3fv(shamanGetUniformLocation(program, name), count,
                       transpose, value);
}

#endif
