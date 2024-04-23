#include <cstdlib>

#include "glutil.h"
#include "logger.h"
#include "shaderutil.h"
#include "vertexutil.h"

int main() {
  auto window = glutil::init();
  Logger::LogInfo("OpenGL version: %s\n", glutil::GetOglVersion().c_str());

  const std::string base_path = "shaders/";
  const std::string vert_shader_path = base_path + "vert.glsl";
  const std::string frag_shader_path = base_path + "frag.glsl";

  ShaderUtil shader_util{};

  const bool success =
      shader_util.CreateShaderProgram(vert_shader_path, frag_shader_path);
  if (!success) {
    Logger::LogError("Failure creating shader program.\n");
    exit(EXIT_FAILURE);
  }

  VertexUtil vertex_util{};
  vertex_util.BindVao();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vertex_util.Draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vertex_util.Cleanup();
  shader_util.Cleanup();
  glfwTerminate();
  return EXIT_SUCCESS;
}