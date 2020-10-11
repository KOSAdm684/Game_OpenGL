#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);
  // try open file than read data
  try
  {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    strcpy(info_log, "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    std::cout << info_log;
  }

  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar * fShaderCode = fragmentCode.c_str();
  GLuint vertex, fragment;
  GLint success;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  
  // check compile vertex shader
  if (!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    std::cout << info_log;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  // check compile fragment shader
  if (!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    std::cout << info_log;
  }
  Program = glCreateProgram();
  glAttachShader(Program, vertex);
  glAttachShader(Program, fragment);
  glLinkProgram(Program);
  glGetProgramiv(Program, GL_LINK_STATUS, &success);
  
  // check linking programm
  if (!success)
  {
    glGetProgramInfoLog(Program, 512, NULL, info_log);
    std::cout << info_log;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader()
{
  glDeleteProgram(Program);
}

void Shader::Use()
{
  glUseProgram(Program);
}

char* Shader::getInfoLog()
{
  return info_log;
}
