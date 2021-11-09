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

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * Shaders
 */
const char vertexShaderPath[] =
    "/home/nbrk/projects/c/shaman/test/shaders/shader1.vert";
const char fragmentShaderPath[] =
    "/home/nbrk/projects/c/shaman/test/shaders/shader1.frag";

/*
 * Vertex data
 */
const GLfloat vertexPositions[] = {
    -0.5f, -0.5f, 0.f,  //
    0.5f,  -0.5f, 0.f,  //
    0.f,   0.5f,  0.f   //
};

const GLfloat vertexNormals[] = {
    0.f, 0.f, 1.f,  //
    0.f, 0.f, 1.f,  //
    0.f, 0.f, 1.f   //
};

const GLfloat vertexColors[] = {
    1.f, 0.f, 0.f, 1.f,  //
    0.f, 1.f, 0.f, 1.f,  //
    0.f, 0.f, 1.f, 1.f   //
};

const GLfloat vertexTexcoords[] = {
    0.0f, 0.0f,  //
    1.0f, 0.0f,  //
    0.5,  1.0f   //
};

int main(int argc, char** argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(1024, 768, "Test 1", NULL, NULL);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  /*
   * Setup
   */

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  /*
   * Alloc enough space
   */
  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(GLfloat) * (sizeof(vertexPositions) + sizeof(vertexNormals) +
                         sizeof(vertexColors) + sizeof(vertexTexcoords)),
      NULL, GL_STATIC_DRAW);
  /*
   * Upload the data. Buffer structure: positions, normals, colors, texcoords.
   */
  GLintptr vertexPositionsOff = 0;
  GLintptr vertexNormalsOff = sizeof(GLfloat) * sizeof(vertexPositions);
  GLintptr vertexColorsOff =
      vertexNormalsOff + sizeof(GLfloat) * sizeof(vertexNormals);
  GLintptr vertexTexcoordsOff =
      vertexColorsOff + sizeof(GLfloat) * sizeof(vertexColors);
  glBufferSubData(GL_ARRAY_BUFFER, vertexPositionsOff,
                  sizeof(GLfloat) * sizeof(vertexPositions), vertexPositions);
  glBufferSubData(GL_ARRAY_BUFFER, vertexNormalsOff,
                  sizeof(GLfloat) * sizeof(vertexNormals), vertexNormals);
  glBufferSubData(GL_ARRAY_BUFFER, vertexColorsOff,
                  sizeof(GLfloat) * sizeof(vertexColors), vertexColors);
  glBufferSubData(GL_ARRAY_BUFFER, vertexTexcoordsOff,
                  sizeof(GLfloat) * sizeof(vertexTexcoords), vertexTexcoords);
  /*
   * Wire the datastream from the buffer as attributes
   */
  //  int ret =
  //      shaman_just_make_program(&program, vertexShaderPath,
  //      fragmentShaderPath);
  int ret = shaman_store_program(0, 0, vertexShaderPath, fragmentShaderPath);
  if (ret != SHAMAN_OK) {
    printf("Error: shaman_store_program() returned %d\n", ret);
    return -1;
  }

  GLuint program;
  // configure program
  shaman_access_program(0, 0, false, &program);
  glEnableVertexAttribArray(glGetAttribLocation(program, "a_position"));
  glEnableVertexAttribArray(glGetAttribLocation(program, "a_normal"));
  glEnableVertexAttribArray(glGetAttribLocation(program, "a_color"));
  glEnableVertexAttribArray(glGetAttribLocation(program, "texcoord"));

  glVertexAttribPointer(glGetAttribLocation(program, "a_position"), 3, GL_FLOAT,
                        GL_FALSE, 0, (void*)vertexPositionsOff);
  glVertexAttribPointer(glGetAttribLocation(program, "a_normal"), 3, GL_FLOAT,
                        GL_FALSE, 0, (void*)vertexNormalsOff);
  glVertexAttribPointer(glGetAttribLocation(program, "a_color"), 4, GL_FLOAT,
                        GL_FALSE, 0, (void*)vertexColorsOff);
  glVertexAttribPointer(glGetAttribLocation(program, "texcoord"), 2, GL_FLOAT,
                        GL_FALSE, 0, (void*)vertexTexcoordsOff);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  /*
   * Render frame
   */
  glClearColor(0.2f, 0.2f, 0.2f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  //  glUseProgram(program);
  shaman_access_program(0, 0, true, NULL);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  glUseProgram(0);

  glfwSwapBuffers(window);

  sleep(5);

  /*
   * Termination
   */
  glDeleteProgram(program);
  glfwTerminate();

  return 0;
}
