#include "glutil.h"

#include <GLFW/glfw3.h>

#include "logger.h"

void glutil::KeyCallback(GLFWwindow* window, const int key, const int scancode,
                         const int action, const int mode) {
  if (action != GLFW_PRESS) {
    return;
  }

  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void glutil::FrameBufferSizeCallback(GLFWwindow* window, const int width,
                                     const int height) {
  Logger::LogInfo("Resizing window to %d %d", width, height);
  glViewport(0, 0, width, height);
}

void glutil::WindowMouseCallback(GLFWwindow* window, double x, double y) {
  Logger::LogInfo("MouseCallback - x position: %.2f, y position: %.2f\n", x, y);
}

void glutil::WindowScrollCallback(GLFWwindow* window, double x_offset,
                                  double y_offset) {
  Logger::LogInfo("ScrollCallback - x offset: %.2f, y offset: %.2f\n", x_offset,
                  y_offset);
}

void glutil::CheckWindowSuccess(const GLFWwindow* window) {
  if (window == nullptr) {
    Logger::LogError("Failed to create GLFW window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
};

void glutil::ErrorCallback(int error, const char* description) {
  Logger::LogError("Error: %s", description);
}

void glutil::SetCallbacks(GLFWwindow* window) {
  glfwSetErrorCallback(ErrorCallback);
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetCursorPosCallback(window, WindowMouseCallback);
  glfwSetScrollCallback(window, WindowScrollCallback);
}

GLFWwindow* glutil::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                        "Basic OGL Example", nullptr, nullptr);

  CheckWindowSuccess(window);
  glfwMakeContextCurrent(window);
  SetCallbacks(window);

  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::LogError("Failed to initialize GLAD\n");
    exit(EXIT_FAILURE);
  }

  return window;
}