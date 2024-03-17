#ifndef GL_UTIL_H
#define GL_UTIL_H

// clang-format off
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace glutil {
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

struct GLFWVersion {
  int major, minor, revision;
};

inline struct GLFWVersion get_glfw_version() {
  struct GLFWVersion version {};
  glfwGetVersion(&version.major, &version.minor, &version.revision);
  return version;
}

// NOTE: requires context initialization to occur beforehand
inline std::string get_open_gl_version() {
  const char* gl_version =
      reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (gl_version == nullptr) {
    std::cerr << "Failed to get OpenGL version\n";
    return std::string{};
  }
  return std::string{gl_version};
}

void key_callback(GLFWwindow* window, const int key, const int scancode,
                  const int action, const int mode);

void framebuffer_size_callback(GLFWwindow* window, const int width,
                               const int height);

void check_window_success(const GLFWwindow* window);

void error_callback(int error, const char* description);

void set_callbacks(GLFWwindow* window);

GLFWwindow* init();

}  // namespace glutil

#endif  // GL_UTIL_H