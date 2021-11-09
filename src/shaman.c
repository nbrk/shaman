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

#include <stdio.h>
#include <stdlib.h>

#define SHAMAN_NUM_TABLES 16
#define SHAMAN_TABLE_NUM_PROGRAMS 16

static GLuint g_store[SHAMAN_NUM_TABLES][SHAMAN_TABLE_NUM_PROGRAMS];

int shaman_just_make_program(GLuint* out_prog,
                             const char* vert_path,
                             const char* frag_path) {
  int ret_code;
  FILE *vert_fp, *frag_fp;
  long vert_size, frag_size;
  char *vert_txt, *frag_txt;
  GLuint vert_sh, frag_sh, program;
  GLint compile_status;

  // initialize for proper cleanup later
  vert_fp = frag_fp = NULL;
  vert_txt = frag_txt = NULL;
  vert_sh = frag_sh = program = 0;

  // open files
  vert_fp = fopen(vert_path, "r");
  frag_fp = fopen(frag_path, "r");
  if (vert_fp == NULL) {
    ret_code = SHAMAN_ERR_VERTEX_OPEN;
    goto cleanup;
  }
  if (frag_fp == NULL) {
    ret_code = SHAMAN_ERR_FRAGMENT_OPEN;
    goto cleanup;
  }

  // determine source sizes
  fseek(vert_fp, 0L, SEEK_END);
  vert_size = ftell(vert_fp);
  rewind(vert_fp);
  fseek(frag_fp, 0L, SEEK_END);
  frag_size = ftell(frag_fp);
  rewind(frag_fp);

  // alloc buffers for the sources, read
  vert_txt = malloc(vert_size);
  if (fread(vert_txt, vert_size, 1, vert_fp) != 1) {
    ret_code = SHAMAN_ERR_VERTEX_IO;
    goto cleanup;
  }
  frag_txt = malloc(frag_size);
  if (fread(frag_txt, frag_size, 1, frag_fp) != 1) {
    ret_code = SHAMAN_ERR_FRAGMENT_IO;
    goto cleanup;
  }

  // compile shaders
  vert_sh = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_sh, 1, (const GLchar**)&vert_txt, NULL);
  glCompileShader(vert_sh);
  glGetShaderiv(vert_sh, GL_COMPILE_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    ret_code = SHAMAN_ERR_VERTEX_PARSE;
    goto cleanup;
  }
  frag_sh = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_sh, 1, (const GLchar**)&frag_txt, NULL);
  glCompileShader(frag_sh);
  glGetShaderiv(frag_sh, GL_COMPILE_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    ret_code = SHAMAN_ERR_FRAGMENT_PARSE;
    goto cleanup;
  }

  // link and validate the program
  program = glCreateProgram();
  glAttachShader(program, vert_sh);
  glAttachShader(program, frag_sh);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    ret_code = SHAMAN_ERR_PROGRAM_LINK;
    goto cleanup;
  }
  glValidateProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    ret_code = SHAMAN_ERR_PROGRAM_VALIDATE;
    goto cleanup;
  }

  // only then do we set the out parameter and ok exit status
  *out_prog = program;
  ret_code = SHAMAN_OK;

  // fall-through to the cleanup...

cleanup:
  if (vert_fp != NULL)
    fclose(vert_fp);
  if (frag_fp != NULL)
    fclose(frag_fp);
  if (vert_txt != NULL)
    free(vert_txt);
  if (frag_txt != NULL)
    free(frag_txt);
  if (vert_sh != 0)
    glDeleteShader(vert_sh);
  if (frag_sh != 0)
    glDeleteShader(frag_sh);
  if (program != 0 && ret_code != SHAMAN_OK)
    glDeleteProgram(program);
  return ret_code;
}

static bool is_location_correct(int table, int row) {
  return !(table < 0 || table >= SHAMAN_NUM_TABLES || row < 0 ||
           row >= SHAMAN_TABLE_NUM_PROGRAMS);
}

int shaman_store_program(int table,
                         int row,
                         const char* vert_path,
                         const char* frag_path) {
  GLuint program;
  int ret_code;

  if (!is_location_correct(table, row))
    return SHAMAN_ERR_LOCATION_BOUNDS;

  if (g_store[table][row] != 0)
    return SHAMAN_ERR_LOCATION_NOT_EMPTY;

  ret_code = shaman_just_make_program(&program, vert_path, frag_path);
  if (ret_code != SHAMAN_OK)
    return ret_code;

  g_store[table][row] = program;

  return SHAMAN_OK;
}

int shaman_access_program(int table, int row, bool useit, GLuint* prog) {
  if (!is_location_correct(table, row))
    return SHAMAN_ERR_LOCATION_BOUNDS;

  if (g_store[table][row] == 0)
    return SHAMAN_ERR_LOCATION_EMPTY;

  if (prog != NULL)
    *prog = g_store[table][row];

  if (useit)
    glUseProgram(g_store[table][row]);

  return SHAMAN_OK;
}

int shaman_discard_program(int table, int row) {
  // TODO: special case: allow -1 values for table and row for bulk discarding

  if (!is_location_correct(table, row))
    return SHAMAN_ERR_LOCATION_BOUNDS;

  // NOTE: allow discarding of empty locations (i.e. by not reporting errors)
  if (g_store[table][row] != 0) {
    glDeleteProgram(g_store[table][row]);
    g_store[table][row] = 0;
  }

  return SHAMAN_OK;
}
