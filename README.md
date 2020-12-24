# Dead-simple shader management library (shaman)

## Purpose
The library helps to group all shaders that are intended to be used in one 
OpenGL program. Users can create such a group by providing

- **distinct shader source files** (i.e. a file for the *vertex* shader, 
a file for the *fragment* shader)
- **or** by providing a **combined source file** where each shader text is
prepended by the string `#shader vertex` or `#shader fragment` respectively.

Example of the combined source file `foo.shaman`:

``` glsl
#shader fragment
#version 130

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.0, 1.0, 0.0, 1.0);
}

#shader vertex
#version 130

in vec4 position;

uniform mat4 mat;

void main()
{
    gl_Position = position;
}
```

The library makes it extremely simple to read such sources from files, to 
compile and in general to keep them together. It is very easy then to create
and link the full OpenGL program from the compiled sources.

## Usage
Structure `shaman_sources_t` represents the group's sources read into memory.
Structure `shaman_compiled_t` represents compiled OpenGL shader ids of the group.

Please see the API header for other documentation for now.

Dead-simple one-liners are:

``` c

  // ... in an OpenGL context
  
  GLuint program1 = shaman_gl_read_distinct_compile_assemble_delete(
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.vert",
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.frag");
      
  GLuint program2 = shaman_gl_read_combined_compile_assemble_delete(
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/basic.shaman");
      
  // now juse use the programs
```

