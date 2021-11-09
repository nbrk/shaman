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

const GLfloat vertexPositions[] = {
    -0.5f, -0.5f, 0.f,  //
    0.5f,  -0.5f, 0.f,  //
    0.f,   0.5f,  0.f   //
};

int main() {
  printf("Start!\n");

  glfwInit();

  GLFWwindow* window = glfwCreateWindow(1024, 768, "Test2", NULL, NULL);

  glfwMakeContextCurrent(window);

  // init extensions in the current OpenGL context
  glewInit();

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sizeof(vertexPositions),
               vertexPositions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // 'in' in shaders

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint program1, program2;
  shaman_just_make_program(
      &program1, "/home/nbrk/projects/c/shaman/test/shaders/shader1.vert",
      "/home/nbrk/projects/c/shaman/test/shaders/shader1.frag");
  program2 = shaman_just_make_program(
      &program2, "/home/nbrk/projects/c/shaman/test/shaders/shader2.vert",
      "/home/nbrk/projects/c/shaman/test/shaders/shader2.frag");

  GLfloat horizoff = 0.f;
  GLuint currentProgram = program2;
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(currentProgram);
    glBindVertexArray(vao);

    // update uniforms
    glUniform1f(glGetUniformLocation(currentProgram, "horizoff"), horizoff);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
      currentProgram = program1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
      currentProgram = program2;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      horizoff -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      horizoff += 0.1;
    }
  }

  glfwTerminate();

  printf("Finish!\n");
  return 0;
}
