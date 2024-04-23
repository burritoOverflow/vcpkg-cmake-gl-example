#include "shaderutil.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "logger.h"

bool ShaderUtil::CreateShaderProgram(const std::string& vert_shader_path,
                                     const std::string& frag_shader_path) {
  GLuint vertex_shader = LoadShader(vert_shader_path, GL_VERTEX_SHADER);
  if (!vertex_shader) {
    Logger::LogError("Failure compiling vertex shader.\n");
    return false;
  }

  GLuint fragment_shader = LoadShader(frag_shader_path, GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    Logger::LogError("Failure compiling fragment shader.\n");
    return false;
  }

  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertex_shader);
  glAttachShader(shader_program_, fragment_shader);
  glLinkProgram(shader_program_);

  if (!CheckShaderErrors(shader_program_, ErrCheckType::kGL_LINK_STATUS)) {
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
    Logger::LogError("File not found for path: %s\n", shader_file_path.c_str());
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
    return GL_FALSE;
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
        Logger::LogError("Error compiling shader; error: %s\n",
                         compile_err_msg.data());
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
        Logger::LogError("Error linking shader program: %s\n",
                         program_link_msg_log.data());
        success = false;
      }
    }
  }
  return success;
}