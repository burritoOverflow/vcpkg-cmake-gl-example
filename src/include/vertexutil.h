#ifndef VERTEX_UTIL_H
#define VERTEX_UTIL_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

class VertexUtil {
 public:
  VertexUtil();

  inline void Cleanup() {
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
  }

  void Draw();

 private:
  GLuint vao_;
  GLuint vbo_;

  // borrowed from LearnOpenGL
  const float vertices_[18] = {
      // positions                            // colors
      0.75f,  -0.75f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.75f, -0.75f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,   0.75f,  0.0f, 0.0f, 0.0f, 1.0f   // top

  };
};

#endif