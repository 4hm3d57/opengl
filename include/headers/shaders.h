#ifndef _SHADERS_H
#define _SHADERS_H

#include "../glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

inline void shader_procedure(const char* vertexPath, const char* fragmentPath, unsigned int& shaderprogram) {
  std::ifstream vshaderFile, fshaderFile;

  vshaderFile.open(vertexPath);
  fshaderFile.open(fragmentPath);

  std::stringstream vshaderStream, fshaderStream;
  vshaderStream << vshaderFile.rdbuf();
  fshaderStream << fshaderFile.rdbuf();

  vshaderFile.close();
  fshaderFile.close();

  std::string vertexCode = vshaderStream.str();
  std::string fragmentCode = fshaderStream.str();

  const char* vshaderSource = vertexCode.c_str();
  const char* fshaderSource = fragmentCode.c_str();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vshaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fshaderSource, NULL);
  glCompileShader(fragmentShader);

  shaderprogram = glCreateProgram();
  glAttachShader(shaderprogram, vertexShader);
  glAttachShader(shaderprogram, fragmentShader);
  glLinkProgram(shaderprogram);
}

inline void vertex_buffer_and_array_stuff(float vertex[], unsigned int index[], unsigned int& vbo, unsigned int& vao, unsigned int& ebo, int vertex_size, int index_size) {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_size, vertex, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vao);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_size, vertex, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * index_size, index, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

inline void use_program(unsigned int shaderprogram) {
  glUseProgram(shaderprogram);
}



#endif
