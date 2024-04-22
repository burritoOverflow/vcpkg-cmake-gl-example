#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <string>

enum class ErrCheckType { kGL_COMPILE_STATUS, kGL_LINK_STATUS };

class ShaderUtil {
 public:
  ShaderUtil() : shader_program_(0) {}

  inline void Cleanup() { glDeleteProgram(shader_program_); }

  bool CreateShaderProgram(const std::string &vert_shader_path,
                           const std::string &frag_shader_path);

 private:
  GLuint shader_program_;

  GLuint LoadShader(const std::string &shader_file_path,
                    const GLuint shader_type);

  bool CheckShaderErrors(const GLuint shader_id, const ErrCheckType type);
};

#endif