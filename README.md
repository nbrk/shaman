# Extremely simple OpenGL shader loading/management library
Shaman is a small, **C89 header-only**, **easy to use** OpenGL shader program 
loading library.

It can be integrated in an existing project in a matter of seconds. The only 
dependency of the implementation code is `GLEW` (popular OpenGL extension loader), which is
only needed for a few OpenGL API calls throughout the library.

## Features
Shaman library has the following features:
- Header-only: just include the header after `#define SHAMAN_IMPLEMENTATION`
- Assemble shader programs from source files or from char arrays
- Uniform setters wrapped in uniform locations lookup
- User-toggled warnings/aborts on missing attrib or uniform location lookups
- No extra data-types, non-invasive design: all returned data is plain OpenGL data

## Usage
You can use `shaman` as a shared library (see `test/test2.c`) or by including 
the `shaman.h` in your project after defining `#define SHAMAN_IMPLEMENTATION`. If
the `SHAMAN_IMPLEMENTATION` is not defined, then only the public API is visible.

The API is very simple: the main function is `shamanMakeProgram(vSrc, fSrc, gSrc)`
that returns the compiled and linked OpenGL program object:

``` c
#define SHAMAN_IMPLEMENTATION
#include "shaman.h"

// ...

GLuint program1 = shamanMakeProgram("shaders/shader1.vert", "shaders/shader1.frag", NULL);
GLuint program2 = shamanMakeProgram("shaders/shader2.vert", "shader2.frag", NULL); 

// ...

glUseProgram(program1);

// ...

shamanSetUniform1f(program1, "horizoff", horizoff);

```

As you can see, you can look up uniform locations or attrib locations (beware the 
unused attributes that could be optimized-away by the GLSL compiler, though):

``` c
// ...
glEnableVertexAttribArray(shamanGetAttribLocation(program, "a_position"));
glVertexAttribPointer(shamanGetAttribLocation(program, "a_position"), 3, GL_FLOAT, GL_FALSE, 0, (void*)vertexPositionsOff);
```

## Header files
There are two header files in the Shaman source directory:
1. `shaman.h`, which contains both API and the implementation (when SHAMAN_IMPLEMENTATION is defined).
** Copy this file alone into your project**.
2. `include/shaman.h`, which contains only the API as part of the `shaman` shared library.
