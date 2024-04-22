#include "shaderutil.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool ShaderUtil::CreateShaderProgram(const std::string& vert_shader_path,
                                     const std::string& frag_shader_path) {
  GLuint vertex_shader = LoadShader(vert_shader_path, GL_VERTEX_SHADER);
  if (!vertex_shader) {
    std::cerr << "Failure compiling vertex shader." << '\n';
    return false;
  }
  GLuint fragment_shader = LoadShader(frag_shader_path, GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    std::cerr << "Failure compiling fragment shader." << '\n';
    return false;
  }

  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertex_shader);
  glAttachShader(shader_program_, fragment_shader);
  glLinkProgram(shader_program_);

  const bool result =
      CheckShaderErrors(shader_program_, ErrCheckType::kGL_LINK_STATUS);
  if (!result) {
    return false;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glUseProgram(shader_program_);

  return true;
}

GLuint ShaderUtil::LoadShader(const std::string& shader_file_path,
                              const GLuint shader_type) {
  std::ifstream in_file(shader_file_path);
  if (!in_file.is_open()) {
    std::cerr << "File not found for path: " << shader_file_path << '\n';
    return false;
  }

  std::stringstream ss;
  ss << in_file.rdbuf();
  const std::string s = ss.str();
  const char* shader_source = s.c_str();

  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_source, NULL);
  glCompileShader(shader);

  GLint compile_result;
  int shader_msg_len;

  if (CheckShaderErrors(shader, ErrCheckType::kGL_COMPILE_STATUS)) {
    return shader;
  } else {
    return false;
  }
}

bool ShaderUtil::CheckShaderErrors(const GLuint id, const ErrCheckType type) {
  int result;
  int err_msg_len;
  bool success{true};

  switch (type) {
    case ErrCheckType::kGL_COMPILE_STATUS: {
      glGetShaderiv(id, GL_COMPILE_STATUS, &result);
      if (!result) {
        auto compile_err_msg = std::vector<char>(err_msg_len + 1);
        glGetShaderInfoLog(id, err_msg_len, &err_msg_len,
                           compile_err_msg.data());
        compile_err_msg.at(err_msg_len) = '\0';
        std::cerr << "Error compiling shader; error: " << compile_err_msg.data()
                  << '\n';
        success = false;
      }
    }

    case ErrCheckType::kGL_LINK_STATUS: {
      glGetProgramiv(shader_program_, GL_LINK_STATUS, &result);
      if (!result) {
        auto program_link_msg_log = std::vector<char>(err_msg_len + 1);
        glGetProgramInfoLog(shader_program_, err_msg_len, &err_msg_len,
                            program_link_msg_log.data());
        program_link_msg_log.at(err_msg_len) = '\0';
        std::cerr << "Error linking shader program: "
                  << program_link_msg_log.data() << '\n';
        success = false;
      }
    }
  }
  return success;
}