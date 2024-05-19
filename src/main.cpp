#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>

#include "glutil.h"
#include "logger.h"
#include "shaderutil.h"
#include "vertexutil.h"

enum class OpType { kADDITION, kSUBTRACTION };

static void SetRotationDegrees(float& rotation_degrees) {
  static const float MAX_DEGREES = 360.f;
  if (rotation_degrees >= MAX_DEGREES) {
    rotation_degrees = 0.0f;
  } else {
    rotation_degrees += 1.0f;
  }
}
static void UpdateCameraPosition(Camera& camera,
                                 OpType& op_type,
                                 const float camera_speed) {
  const static float UPPER_BOUND = 10.0;
  const static float LOWER_BOUND = 3.0;
  auto z_position = camera.camera_position_.z;

  // these are unitutive, admittedly
  if (z_position >= UPPER_BOUND && op_type == OpType::kSUBTRACTION) {
    Logger::LogInfo(
        "Upper bound of %.2f exceeded with value: %.2f; changing to addition\n",
        UPPER_BOUND, z_position);
    op_type = OpType::kADDITION;
  }
  if (z_position <= LOWER_BOUND && op_type == OpType::kADDITION) {
    Logger::LogInfo(
        "Lower bound of %.2f exceeded with value: %.2f; changing to "
        "subtraction\n",
        LOWER_BOUND, z_position);
    op_type = OpType::kSUBTRACTION;
  }

  if (op_type == OpType::kADDITION) {
    camera.camera_position_ += camera_speed * camera.camera_front_;
  } else if (op_type == OpType::kSUBTRACTION) {
    camera.camera_position_ -= camera_speed * camera.camera_front_;
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
  float delta_time = 0.0f;
  float last_frame = 0.0f;

  auto op_type = OpType::kSUBTRACTION;

  while (!glfwWindowShouldClose(window)) {
    const float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vertex_util.Draw();
    shader_util.SetUniformFloat(rotation_degrees, ROTATION_DEGREES_STR);
    SetRotationDegrees(rotation_degrees);

    const float camera_speed = 0.9 * delta_time;
    UpdateCameraPosition(shader_util.camera_, op_type, camera_speed);

    // TODO find more efficient way to do this
    const auto view_matrix = glm::lookAt(shader_util.camera_.camera_position_,
                                         shader_util.camera_.camera_front_,
                                         shader_util.camera_.camera_up_);

    shader_util.SetMatrixType(MatrixType::kVIEW_MATRIX, view_matrix);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vertex_util.Cleanup();
  shader_util.Cleanup();
  glfwTerminate();
  return EXIT_SUCCESS;
}
