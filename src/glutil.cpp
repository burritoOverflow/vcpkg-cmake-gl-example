#include "glutil.h"

void glutil::key_callback(GLFWwindow* window, const int key, const int scancode,
                          const int action, const int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void glutil::framebuffer_size_callback(GLFWwindow* window, const int width,
                                       const int height) {
  glViewport(0, 0, width, height);
}

void glutil::check_window_success(const GLFWwindow* window) {
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
};

void glutil::error_callback(int error, const char* description) {
  std::cerr << "Error: " << description << '\n';
}

void glutil::set_callbacks(GLFWwindow* window) {
  glfwSetErrorCallback(error_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
}

GLFWwindow* glutil::init() {
  glfwInit();
  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "GL Stuff Example", NULL, NULL);

  check_window_success(window);
  glfwMakeContextCurrent(window);
  set_callbacks(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << '\n';
    exit(EXIT_FAILURE);
  }

  return window;
}