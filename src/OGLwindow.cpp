#include "OGLwindow.h"


GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower left corner
    0.5f,  -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower right corner
    0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f   // Upper corner
};

OGLwindow::OGLwindow(int x, int y) {
  std::cout << glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f,  // Lower left corner
      0.5f,  -0.5f, 0.0f,  // Lower right corner
      0.0f,  0.1f,  0.0f   // Upper corner
  };

  window = glfwCreateWindow(x, y, "HI MOM", NULL, NULL);
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
















// clang-format off
#include <chrono>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
//#include "im.txt"

unsigned char suzanne[1024*1024*4];
std::chrono::steady_clock::time_point start;
void start_timer() {
  start = std::chrono::high_resolution_clock::now();
}
void print_timer() {
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << "\n";
}
//unsigned char suzanne[];
// clang-format on
//            Vertices coordinates
GLfloat vertices[] = {
    //  COORDINATES    /     COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Lower left corner
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Upper right corner
    0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] = {
    0, 2, 1,  // Upper triangle
    0, 3, 2   // Lower triangle
};

GLFWwindow* window;

std::string get_file_contents(const char* filename) {
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

GLuint shadID;
GLuint VAO1ID;
GLuint VBO1ID;
GLuint EBO1ID;

GLuint suzanneID;
GLenum texType;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, 800, 800);

  {                                                              // Generates Shader object using shaders default.vert and default.frag
    std::string vertexCode = get_file_contents("default.vert");  // Read vertexFile and fragmentFile and store the strings
    std::string fragmentCode = get_file_contents("default.frag");

    const char* vertexSource = vertexCode.c_str();  // Convert the shader source strings into character arrays
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);      // Create Vertex Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  // Create Fragment Shader Object and get its reference
    shadID = glCreateProgram();                                  // Create Shader Program Object and get its reference
    glShaderSource(vertexShader, 1, &vertexSource, NULL);        // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);    // Attach Fragment Shader source to the Fragment Shader Object
    glCompileShader(vertexShader);                               // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);                             // Compile the Vertex Shader into machine code
    glAttachShader(shadID, vertexShader);                        // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shadID, fragmentShader);                      //
    glLinkProgram(shadID);                                       // Wrap-up/Link all the shaders together into the Shader Program
    {                                                            // Checks if Shader compiled succesfully
      GLint hasCompiled;
      char infoLog[1024];

      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
      if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << "VERTEX" << "\n" << infoLog << std::endl;
      }
      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
      if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << "FRAGMENT" << "\n" << infoLog << std::endl;
      }
      glGetProgramiv(shadID, GL_LINK_STATUS, &hasCompiled);
      if (hasCompiled == GL_FALSE) {
        glGetProgramInfoLog(shadID, 1024, NULL, infoLog);
        std::cout << "SHADER_LINKING_ERROR for:" << "PROGRAM" << "\n" << infoLog << std::endl;
      }
    }

    glDeleteShader(vertexShader);  // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(fragmentShader);
  }
  glGenVertexArrays(1, &VAO1ID);  // Generates Vertex Array Object and binds it
  glBindVertexArray(VAO1ID);

  // Generates Vertex Buffer Object and links it to vertices
  glGenBuffers(1, &VBO1ID);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1ID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Generates Element Buffer Object and links it to indices
  glGenBuffers(1, &EBO1ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  {  // Links VBO attributes such as coordinates and colors to VAO
    GLuint layout = 0;
    GLuint numComponents = 3;
    GLenum type = GL_FLOAT;
    GLsizeiptr stride = 8 * sizeof(float);
    void* offset = (void*)0;

    glBindBuffer(GL_ARRAY_BUFFER, VBO1ID);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  {
    GLuint layout = 1;
    GLuint numComponents = 3;
    GLenum type = GL_FLOAT;
    GLsizeiptr stride = 8 * sizeof(float);
    void* offset = (void*)(3 * sizeof(float));

    glBindBuffer(GL_ARRAY_BUFFER, VBO1ID);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  {
    GLuint layout = 2;
    GLuint numComponents = 2;
    GLenum type = GL_FLOAT;
    GLsizeiptr stride = 8 * sizeof(float);
    void* offset = (void*)(6 * sizeof(float));

    glBindBuffer(GL_ARRAY_BUFFER, VBO1ID);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);  // Unbind all to prevent accidentally modifying them
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  GLuint uniID = glGetUniformLocation(shadID, "scale");  // Gets ID of uniform called "scale"
  //GLuint imgID = glGetUniformLocation(shadID, "img");  // Gets ID of uniform called "scale"

  {
    texType = GL_TEXTURE_2D;
    GLenum slot = GL_TEXTURE0;
    GLenum format = GL_RGBA;
    GLenum pixelType = GL_UNSIGNED_BYTE;

    glGenTextures(1, &suzanneID);  // Generates an OpenGL texture object
    glActiveTexture(slot);         // Assigns the texture to a Texture Unit
    glBindTexture(texType, suzanneID);

    //glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);  // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, 1024, 1024, 0, format, pixelType, suzanne);  // Assigns the image to the OpenGL Texture object
    //glGenerateMipmap(texType);                                                     // Generates MipMaps

    glBindTexture(texType, 0);  // Unbinds the OpenGL Texture object so that it can't accidentally be modified
  }

  {
    const char* uniform = "tex0";
    GLuint unit = 0;
    GLuint texUni = glGetUniformLocation(shadID, uniform);  // Gets the location of the uniform
    glUseProgram(shadID);                                   // Shader needs to be activated before changing the value of a uniform
    glUniform1i(texUni, unit);                              // Sets the value of the uniform
  }

  /*{
    const char* uniform = "img";
    GLuint unit = 0;
    GLuint texUni = glGetUniformLocation(shadID, uniform);  // Gets the location of the uniform
    glUseProgram(shadID);                                   // Shader needs to be activated before changing the value of a uniform
    glUniform3uiv(texUni, 1024*1024, (unsigned int*)suzanne);                              // Sets the value of the uniform
  }*/

  // Main while loop
  int a = 0;
  int b = 0;
  while (!glfwWindowShouldClose(window)) {
    start_timer();
    for(int i = 0; i<(1024*1024*4);i+=4){
      suzanne[i+0]++;
      suzanne[i+1];
      suzanne[i+2];
      //std::cout << b << std::endl;
    }
      //suzanne[b++] = 0;
      //suzanne[b++] = 0;
      //suzanne[b++] = 0;
      //suzanne[b++] = 0;


    glBindTexture(GL_TEXTURE_2D, suzanneID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, suzanne);  // Assigns the image to the OpenGL Texture object

  //  std::cout << a << '\n';
//    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);              // Specify the color of the background
//    glClear(GL_COLOR_BUFFER_BIT);                         // Clean the back buffer and assign the new color to it
    glUseProgram(shadID);                                 // Tell OpenGL which Shader Program we want to use
//    glUniform1f(uniID, ((float)a++) / 100);               // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
    //glUniform4uiv(imgID, 1024, testingness);
    glBindTexture(texType, suzanneID);                    // Binds texture so that is appears in rendering
    glBindVertexArray(VAO1ID);                            // Bind the VAO so OpenGL knows to use it
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // Draw primitives, number of indices, datatype of indices, index of indices
    glfwSwapBuffers(window);                              // Swap the back buffer with the front buffer
    glfwPollEvents();                                     // Take care of all GLFW events
    //print_timer();
  }

  glDeleteVertexArrays(1, &VAO1ID);  // Delete all the objects we've created
  glDeleteBuffers(1, &VBO1ID);
  glDeleteBuffers(1, &EBO1ID);
  glDeleteTextures(1, &suzanneID);
  glDeleteProgram(shadID);
  glfwDestroyWindow(window);  // Delete window before ending the program
  glfwTerminate();            // Terminate GLFW before ending the program
  return 0;
}