#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <map>
#include <string>

enum class ErrCheckType { kGL_COMPILE_STATUS, kGL_LINK_STATUS };
enum class MatrixType { kMODEL_MATRIX, kVIEW_MATRIX, kPROJECTION_MATRIX };

struct Camera {
  glm::vec3 camera_position_;  // eye
  glm::vec3 camera_front_;     // at
  glm::vec3 camera_up_;        // up
};

class ShaderUtil {
 public:
  ShaderUtil() : shader_program_(0), camera_(Camera{}) {}

  Camera camera_;

  inline void Cleanup() { glDeleteProgram(shader_program_); }

  bool CreateShaderProgram(const std::string &vert_shader_path,
                           const std::string &frag_shader_path);

  glm::mat4 &GetMatrix(const MatrixType matrix_type);

  void SetMatrixType(const MatrixType matrix_type, const glm::mat4 &matrix);

  GLuint SetUniformFloat(const float f, const std::string &name);

 private:
  GLuint shader_program_;

  glm::mat4 model_matrix_;
  glm::mat4 view_matrix_;
  glm::mat4 projection_matrix_;

  // collect each uniform with the name and identifer
  // where k is the name for the uniform and v is the returned GLuint location
  // for this new Uniform
  std::map<std::string, GLuint> uniform_locations_;

  GLuint LoadShader(const std::string &shader_file_path,
                    const GLuint shader_type);

  bool CheckShaderErrors(const GLuint shader_id, const ErrCheckType type);

  // wrapper to set the location for the given matrix
  GLuint GlSetMatrix(const std::string &name, const glm::mat4 &matrix);

  void SetModelViewProjectionMatrix();
};

#endif
