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
