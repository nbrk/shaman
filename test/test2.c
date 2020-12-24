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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

static const GLfloat vertex_buffer_positions[] = {
    -0.5f, -0.5f, -0.5f, // x
    0.f,   0.5f,  -0.5f, // y
    0.5f,  -0.5f, -0.5f, // z
};

static const GLfloat vertex_buffer_colors[] = {
    1.0f, 0.0f, 0.0f, // first vertex
    0.0f, 1.0f, 0.0f, // second...
    0.0f, 0.0f, 1.0f,
};

int main() {
  printf("Start!\n");

  glfwInit();

  GLFWwindow *window = glfwCreateWindow(1024, 768, "Test2", NULL, NULL);

  glfwMakeContextCurrent(window);

  // init extensions in the current OpenGL context
  glewInit();

  // Defult VAO -- needed for core profile
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //  shaman_sources_t p1src = shaman_read_distinct(
  //      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.vert",
  //      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.frag");
  //  shaman_sources_t p2src = shaman_read_combined(
  //      "/usr/home/nbrk/projects/cc/shaman/test/shaders/basic.shaman");
  //  shaman_compiled_t p1comp = shaman_gl_compile(p1src);
  //  shaman_compiled_t p2comp = shaman_gl_compile(p2src);
  //  GLuint program1 = shaman_gl_assemble_program(shaman_gl_compile(p1src),
  //  NULL); GLuint program2 = shaman_gl_assemble_program(p2comp, NULL);
  //  shaman_gl_delete(p1comp);
  //  shaman_gl_delete(p2comp);

  GLuint program1 = shaman_gl_read_distinct_compile_assemble_delete(
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.vert",
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/shader.frag");
  GLuint program2 = shaman_gl_read_combined_compile_assemble_delete(
      "/usr/home/nbrk/projects/cc/shaman/test/shaders/basic.shaman");

  if (program1 == 0 || program2 == 0) {
    printf("Can't load shader programs!\n");
    return EXIT_FAILURE;
  }

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_positions),
               vertex_buffer_positions, GL_STATIC_DRAW);

  mat4 mat;
  vec3 eye = {0.f, 0.f, 0.f};
  vec3 dir = {0.f, 0.f, -1.0f};
  vec3 up = {0.f, 1.f, 0.0f};

  GLuint program = program1;
  GLfloat horizoff = 0.f;

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glUseProgram(program);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // 'in' in shaders

    // update uniforms
    GLint horizoff_u = glGetUniformLocation(program, "horizoff");
    //    GLint mat_u = glGetUniformLocation(program, "mat");
    glUniform1f(horizoff_u, horizoff);
    //    glm_look(eye, dir, up, mat);
    //    glUniformMatrix4fv(mat_u, 1, GL_FALSE, (float*)mat);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
      program = program1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
      program = program2;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      horizoff -= 0.1;
      //      dir[0] -= 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      horizoff += 0.1;
      //      dir[0] += 0.1f;
    }
  }

  glfwTerminate();

  printf("Finish!\n");
  return 0;
}
