#include "glutil.h"

#include <GLFW/glfw3.h>

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
  glViewport(0, 0, width, height);
}

void glutil::CheckWindowSuccess(const GLFWwindow* window) {
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
};

void glutil::ErrorCallback(int error, const char* description) {
  std::cerr << "Error: " << description << '\n';
}

void glutil::SetCallbacks(GLFWwindow* window) {
  glfwSetErrorCallback(ErrorCallback);
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
  glfwSetKeyCallback(window, KeyCallback);
}

GLFWwindow* glutil::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "GL Stuff Example", nullptr, nullptr);

  CheckWindowSuccess(window);
  glfwMakeContextCurrent(window);
  SetCallbacks(window);

  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << '\n';
    exit(EXIT_FAILURE);
  }

  return window;
}