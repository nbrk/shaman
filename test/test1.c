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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *combined_path =
    "/usr/home/nbrk/projects/cc/shaman/test/shaders/basic.shaman";
static const char *vert_path =
    "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.vert";
static const char *frag_path =
    "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.frag";

static const char *test_text =
    "Hello\n#shader foo\nTesting test\nFoobar\n#shader "
    "koo\nSomething at the end\n";

int main(int argc, char **argv) {
  shaman_sources_t sources1 = shaman_read_combined(combined_path);
  shaman_sources_t sources2 = shaman_read_distinct(vert_path, frag_path);

  printf("====== Combined ======\n");
  printf("Vertex text:\n");
  printf("%s======\n", sources1.vertex_text);
  printf("Fragment text:\n");
  printf("%s======\n", sources1.fragment_text);

  printf("====== Separate ======\n");
  printf("Vertex text:\n");
  printf("%s======\n", sources2.vertex_text);
  printf("Fragment text:\n");
  printf("%s======\n", sources2.fragment_text);

  return EXIT_SUCCESS;
}
