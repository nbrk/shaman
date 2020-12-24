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

/*
 * Simple shader management library (shaman).
 */

/**
 * @brief Describes sources for a set of shaders
 */
typedef struct {
  char *vertex_text;
  char *fragment_text;
} shaman_sources_t;

/**
 * @brief Decribes created and compiled shaders
 */
typedef struct {
  unsigned int vertex_id;
  char *vertex_error;
  unsigned int fragment_id;
  char *fragment_error;
} shaman_compiled_t;

/**
 * @brief Parse shaders from the combined source file. Expects "#shader vertex",
 * "#shader fragment", etc. designators in the source code.
 * @param path
 * @return
 */
extern shaman_sources_t shaman_read_combined(const char *path);

/**
 * @brief Parse shaders from distinct, non-combined (so not annotated by
 * #shader) source files
 * @param vertex_path
 * @param fragment_path
 * @return
 */
extern shaman_sources_t shaman_read_distinct(const char *vertex_path,
                                             const char *fragment_path);

/**
 * @brief Check if all the sources are present
 * @param sources
 * @return 0 on success
 */
extern int shaman_read_ok(shaman_sources_t sources);

/**
 * @brief Create and compile parsed shaders using the current OpenGL context
 * @param parsed
 * @return
 */
extern shaman_compiled_t shaman_gl_compile(shaman_sources_t sources);

/**
 * @brief Delete the shaders (compiled results) from the OpenGL context and free
 * any infolog memory
 * @param sources
 */
extern void shaman_gl_delete(shaman_compiled_t compiled);

/**
 * @brief Check if all the shaders were compiled successfully
 * @param compiled
 * @return 0 on success
 */
extern int shaman_compiled_ok(shaman_compiled_t compiled);

/**
 * @brief Create and link new program using the compiled shaders
 * @param compiled
 * @param infolog [out]
 * @return opengl program id or 0 on error
 */
extern unsigned int shaman_gl_assemble_program(shaman_compiled_t compiled,
                                               char **infolog);

extern unsigned int
shaman_gl_read_distinct_compile_assemble_delete(const char *vertex_path,
                                                const char *fragment_path);

extern unsigned int
shaman_gl_read_combined_compile_assemble_delete(const char *path);
