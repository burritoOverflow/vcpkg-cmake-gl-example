#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>

#include "glutil.h"
#include "logger.h"
#include "shaderutil.h"
#include "vertexutil.h"

static void SetRotationDegrees(float &rotation_degrees) {
  if (rotation_degrees >= 360.0f) {
    rotation_degrees = 0.0f;
  } else {
    rotation_degrees += 1.0f;
  }
}

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

  float rotation_degrees{0.0};

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vertex_util.Draw();

    // TODO find a more efficient way to do this
    auto model = shader_util.GetMatrix(MatrixType::kMODEL_MATRIX);
    model = glm::rotate(model, glm::radians(rotation_degrees),
                        glm::vec3(0.0f, 4.0f, 0.0f));
    shader_util.SetMatrixType(MatrixType::kMODEL_MATRIX, model);

    SetRotationDegrees(rotation_degrees);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vertex_util.Cleanup();
  shader_util.Cleanup();
  glfwTerminate();
  return EXIT_SUCCESS;
}