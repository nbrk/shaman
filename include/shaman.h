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

#include <GL/glew.h>
#include <stdbool.h>

/*
 * Simple OpenGL shader management library (shaman).
 *
 */

/**
 * @brief Error/status codes returned from the shaman's functions
 */
enum {
  SHAMAN_OK,
  SHAMAN_ERR_LOCATION_BOUNDS,
  SHAMAN_ERR_LOCATION_NOT_EMPTY,
  SHAMAN_ERR_LOCATION_EMPTY,
  SHAMAN_ERR_VERTEX_OPEN,
  SHAMAN_ERR_FRAGMENT_OPEN,
  SHAMAN_ERR_VERTEX_IO,
  SHAMAN_ERR_FRAGMENT_IO,
  SHAMAN_ERR_VERTEX_PARSE,
  SHAMAN_ERR_FRAGMENT_PARSE,
  SHAMAN_ERR_PROGRAM_LINK,
  SHAMAN_ERR_PROGRAM_VALIDATE,
};

/**
 * @brief Assemble complete shader program from source files and just output the
 * program's OpenGL object
 * @param[out] out_prog
 * @param vert_path
 * @param frag_path
 * @return error code or SHAMAN_OK
 */
extern int shaman_just_assemble_program(GLuint* out_prog,
                                        const char* vert_path,
                                        const char* frag_path);

/**
 * @brief Assemble the program and store it at the given 'location' inside the
 * shaman's internal storage.
 *
 * @param table selects the table
 * @param row selects the record inside the table
 * @param vert_path
 * @param frag_path
 * @return error code or SHAMAN_OK
 */
extern int shaman_store_program(int table,
                                int row,
                                const char* vert_path,
                                const char* frag_path);

/**
 * @brief Fetch the program that was stored to a location.
 * @param table
 * @param row
 * @param useit whether to call glUseProgram() upon return
 * @param[out] prog the program's OpenGL object
 * @return error code or SHAMAN_OK
 */
extern int shaman_access_program(int table, int row, bool useit, GLuint* prog);

/**
 * @brief Discard one ore more programs stored at a given location.
 * @param table valid table number, or -1 to discard all programs in all tables
 * @param row valid row number, or -1 to discard all programs in the given table
 * @return error code or SHAMAN_OK
 */
extern int shaman_discard_program(int table, int row);
