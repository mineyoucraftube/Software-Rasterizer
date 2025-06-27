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

GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower left corner
    0.5f,  -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower right corner
    0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f   // Upper corner
};

OGLwindow::OGLwindow(int x, int y) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,  // Lower left corner
      0.5f,  -0.5f, 0.0f,  // Lower right corner
      0.0f,  0.1f,  0.0f   // Upper corner
  };

  GLFWwindow* window = glfwCreateWindow(x, y, "HI MOM", NULL, NULL);
  if (window == NULL) {
    std::cout << "fuck" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, x, y);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);      // Create Vertex Shader Object and get its reference
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  // Create Fragment Shader Object and get its reference

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);      // Attach Vertex Shader source to the Vertex Shader Object
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);  // Attach Fragment Shader source to the Fragment Shader Object

  glCompileShader(vertexShader);    // Compile the Vertex Shader into machine code
  glCompileShader(fragmentShader);  // Compile the Vertex Shader into machine code

  shaderProgram = glCreateProgram();            // Create Shader Program Object and get its reference
  glAttachShader(shaderProgram, vertexShader);  // Attach the Vertex and Fragment Shaders to the Shader Program
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);  // Wrap-up/Link all the shaders together into the Shader Program

  glDeleteShader(vertexShader);  // Delete the now useless Vertex and Fragment Shader objects
  glDeleteShader(fragmentShader);

  glGenVertexArrays(1, &VAO);  // Generate the VAO and VBO with only 1 object each
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);  // Make the VAO the current Vertex Array Object by binding it

  glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         // Bind the VBO specifying it's a GL_ARRAY_BUFFER
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Introduce the vertices into the VBO

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
  glEnableVertexAttribArray(0);                                                  // Enable the Vertex Attribute so that OpenGL knows to use it

  glBindBuffer(GL_ARRAY_BUFFER, 0);  // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
  glBindVertexArray(0);
}

void OGLwindow::display_image(Image* image) {
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);  // Specify the color of the background
  glClear(GL_COLOR_BUFFER_BIT);             // Clean the back buffer and assign the new color to it
  glUseProgram(shaderProgram);              // Tell OpenGL which Shader Program we want to use
  glBindVertexArray(VAO);                   // Bind the VAO so OpenGL knows to use it
  glDrawArrays(GL_TRIANGLES, 0, 3);         // Draw the triangle using the GL_TRIANGLES primitive
  glfwSwapBuffers(window);                  // Swap the back buffer with the front buffer
  glfwPollEvents();                         // Take care of all GLFW events
}

int OGLwindow::shouldclose() {
  return glfwWindowShouldClose(window);
}

OGLwindow::~OGLwindow() {
  glDeleteVertexArrays(1, &VAO);  // Delete all the objects we've created
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);  // Delete window before ending the program
  glfwTerminate();            // Terminate GLFW before ending the program
}
