#ifndef GL_UTIL_H
#define GL_UTIL_H

// clang-format off
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "logger.h"

namespace glutil {
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

struct GLFWVersion {
  int major_, minor_, revision_;
};

inline struct GLFWVersion GetGlfwVersion() {
  struct GLFWVersion version {};
  glfwGetVersion(&version.major_, &version.minor_, &version.revision_);
  return version;
}

// NOTE: requires context initialization to occur beforehand
inline std::string GetOglVersion() {
  const char* gl_version =
      reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (gl_version == nullptr) {
    Logger::LogError("Failed to get OpenGL version\n");
    return std::string{};
  }
  return std::string{gl_version};
}

void WindowMouseCallback(GLFWwindow* window, double x, double y);

void WindowScrollCallback(GLFWwindow* window, double x, double y);

void KeyCallback(GLFWwindow* window, const int key, const int scancode,
                 const int action, const int mode);

void FrameBufferSizeCallback(GLFWwindow* window, const int width,
                             const int height);

void CheckWindowSuccess(const GLFWwindow* window);

void ErrorCallback(int error, const char* description);

void SetCallbacks(GLFWwindow* window);

GLFWwindow* init();

}  // namespace glutil

#endif  // GL_UTIL_H