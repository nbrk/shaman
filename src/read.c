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
#include "shaman_internal.h"

#include <shaman.h>
#include <stdlib.h>

extern int shaman_read_ok(shaman_sources_t sources) {
  if (sources.fragment_text != NULL && sources.vertex_text != NULL)
    return 0;
  else
    return -1;
}

shaman_sources_t shaman_read_distinct(const char *vertex_path,
                                      const char *fragment_path) {
  shaman_sources_t sources;
  FILE *vertex_fp = fopen(vertex_path, "r");
  FILE *fragment_fp = fopen(fragment_path, "r");
  if (vertex_fp == NULL || fragment_fp == NULL) {
    sources.vertex_text = NULL;
    sources.fragment_text = NULL;
    return sources;
  }
  sources.vertex_text = file_get_contents(vertex_fp);
  sources.fragment_text = file_get_contents(fragment_fp);
  fclose(vertex_fp);
  fclose(fragment_fp);
  return sources;
}

shaman_sources_t shaman_read_combined(const char *path) {
  shaman_sources_t sources;
  sources.fragment_text = NULL;
  sources.vertex_text = NULL;

  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    // TODO some indication of error
    return sources;
  }
  char *contents = file_get_contents(fp);
  fclose(fp);

  if (contents == NULL)
    return sources;
  sources.fragment_text =
      contents_get_section(contents, "#shader fragment", "#shader");
  sources.vertex_text =
      contents_get_section(contents, "#shader vertex", "#shader");
  free(contents);
  return sources;
}
