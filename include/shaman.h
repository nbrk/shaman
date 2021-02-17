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
 * Don't forget to call shamanInit() before use of the functions.
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
extern void shamanInitInContext(void);

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
