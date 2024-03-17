#include <iostream>

#include "glutil.h"

int main() {
  auto window = glutil::init();
  std::cout << "OpenGL version: " << glutil::get_open_gl_version() << '\n';

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}