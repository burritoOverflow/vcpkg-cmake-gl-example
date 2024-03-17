// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

struct GLFWVersion {
  int major, minor, revision;
};

static struct GLFWVersion get_glfw_version() {
  struct GLFWVersion version {};
  glfwGetVersion(&version.major, &version.minor, &version.revision);
  return version;
}

// NOTE: requires context initialization to occur beforehand
static std::string get_open_gl_version() {
  const char* gl_version =
      reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (gl_version == nullptr) {
    std::cerr << "Failed to get OpenGL version\n";
  }
  return std::string{gl_version};
}

static void key_callback(GLFWwindow* window, const int key, const int scancode,
                         const int action, const int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void framebuffer_size_callback(GLFWwindow* window, const int width,
                                      const int height) {
  glViewport(0, 0, width, height);
}

static void check_window_success(const GLFWwindow* window) {
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
};

static void error_callback(int error, const char* description) {
  std::cerr << "Error: " << description << '\n';
}

static void set_callbacks(GLFWwindow* window) {
  glfwSetErrorCallback(error_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
}

GLFWwindow* init() {
  glfwInit();
  const auto version = get_glfw_version();

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "GL Stuff Example", NULL, NULL);

  check_window_success(window);
  glfwMakeContextCurrent(window);
  set_callbacks(window);

  return window;
}

int main() {
  auto window = init();

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}