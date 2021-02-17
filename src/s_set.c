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
#include <shaman.h>
#include <stdbool.h>

#include <GL/glew.h>

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
