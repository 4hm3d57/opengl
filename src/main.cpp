#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include <iostream>
#include "../include/headers/shaders.h"

#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", NULL, NULL);
  if(window == NULL){
    std::cout << "Failed to load GLFW" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "glad failed" << std::endl;
    return -1;
  }

  float rectangle_position[] = {
    //top right
    0.5f, 0.5f, 0.0f,
    //bottom right
    0.5f, -0.5f, 0.0f,
    //top left
    -0.5f, 0.5f, 0.0f,
    //bottom left
    -0.5f, -0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 1
  };

  unsigned int shaderProgram;
  shader_procedure("shaders/default.vert", "shaders/default.frag", shaderProgram);

  unsigned int VBO, VAO, EBO;
  int rectanglePosition_size = sizeof(rectangle_position) / sizeof(rectangle_position[0]);
  int indices_size = sizeof(indices) / sizeof(indices[0]);
  vertex_buffer_and_array_stuff(rectangle_position, indices, VBO, VAO, EBO, rectanglePosition_size, indices_size);
  

  while(!glfwWindowShouldClose(window)){
    processInput(window);
    use_program(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(width, height, 0, 0);
}

void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}
