#include "shaderutil.h"

#include <fstream>
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "glutil.h"
#include "logger.h"

const static std::string MODEL_STR = "model";
const static std::string VIEW_STR = "view";
const static std::string PROJECTION_STR = "projection";

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

  SetModelViewProjectionMatrix();

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

glm::mat4 ShaderUtil::GetMatrix(const MatrixType matrix_type) {
  switch (matrix_type) {
    case MatrixType::kMODEL_MATRIX: {
      return this->model_matrix_;
    }
    case MatrixType::kVIEW_MATRIX: {
      return this->view_matrix_;
    }
    case MatrixType::kPROJECTION_MATRIX: {
      return this->projection_matrix_;
    }
  }
}

void ShaderUtil::SetMatrixType(const MatrixType matrix_type,
                               const glm::mat4& matrix) {
  std::string model_type_str{};
  switch (matrix_type) {
    case MatrixType::kMODEL_MATRIX: {
      model_type_str = MODEL_STR;
      model_location_ = SetMatrix(model_type_str, matrix);
      break;
    }
    case MatrixType::kVIEW_MATRIX: {
      model_type_str = VIEW_STR;
      view_location_ = SetMatrix(model_type_str, matrix);
      break;
    }
    case MatrixType::kPROJECTION_MATRIX: {
      model_type_str = PROJECTION_STR;
      projection_location_ = SetMatrix(model_type_str, matrix);
      break;
    }
    default:
      throw std::invalid_argument{"Matrix type not found"};
  }

  Logger::LogInfo("Setting %s matrix with value\n", model_type_str.c_str());
}

GLuint ShaderUtil::SetMatrix(const std::string& name, const glm::mat4& matrix) {
  GLuint location = glGetUniformLocation(shader_program_, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  return location;
}

void ShaderUtil::SetModelViewProjectionMatrix() {
  model_matrix_ = glm::mat4(1.0f);
  SetMatrixType(MatrixType::kMODEL_MATRIX, model_matrix_);

  view_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  SetMatrixType(MatrixType::kVIEW_MATRIX, view_matrix_);

  projection_matrix_ = glm::perspective(
      glm::radians(35.0f),
      static_cast<float>(glutil::WIDTH) / static_cast<float>(glutil::HEIGHT),
      0.1f, 100.0f);
  SetMatrixType(MatrixType::kPROJECTION_MATRIX, projection_matrix_);
}