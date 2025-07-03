#pragma once
// clang-format off: why tf does clang format reorders the includes??
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "graphics.h"

class OGLwindow {
 private:
  GLFWwindow* window;
  GLuint shaderProgram;
  // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
  GLuint VAO, VBO;

  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n\0";

  const char* fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
      "}\n\0";

 public:
  OGLwindow(int x, int y);
  void display_image(Image* image);
  int shouldclose();
  ~OGLwindow();
};
