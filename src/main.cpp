#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>

#include "glutil.h"
#include "logger.h"
#include "shaderutil.h"
#include "vertexutil.h"

static void SetRotationDegrees(float &rotation_degrees) {
  static const float MAX_DEGREES = 360.f;
  if (rotation_degrees >= MAX_DEGREES) {
    rotation_degrees = 0.0f;
  } else {
    rotation_degrees += 1.0f;
  }
}

int main() {
  auto window = glutil::init();

  Logger::LogInfo("OpenGL version: %s\n", glutil::GetOglVersion().c_str());

  const std::string BASE_PATH = "shaders/";
  const std::string VERT_SHADER_PATH = BASE_PATH + "vert.glsl";
  const std::string FRAG_SHADER_PATH = BASE_PATH + "frag.glsl";

  // name for the uniform associated with rotation
  const std::string ROTATION_DEGREES_STR = "rotationDegrees";

  ShaderUtil shader_util{};

  const bool success =
      shader_util.CreateShaderProgram(VERT_SHADER_PATH, FRAG_SHADER_PATH);

  if (!success) {
    Logger::LogError("Failure creating shader program.\n");
    exit(EXIT_FAILURE);
  }

  VertexUtil vertex_util{};
  vertex_util.BindVao();

  float rotation_degrees{0.0};

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vertex_util.Draw();
    shader_util.SetUniformFloat(rotation_degrees, ROTATION_DEGREES_STR);
    SetRotationDegrees(rotation_degrees);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vertex_util.Cleanup();
  shader_util.Cleanup();
  glfwTerminate();
  return EXIT_SUCCESS;
}