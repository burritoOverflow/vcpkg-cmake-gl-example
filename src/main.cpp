#include <cstdlib>
#include <iostream>

#include "glutil.h"

int main() {
  auto window = glutil::init();
  std::cout << "OpenGL version: " << glutil::get_open_gl_version() << '\n';

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}