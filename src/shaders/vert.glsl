#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float rotationDegrees;

out vec3 inColor;

// both examples are found in "Interactive Computer Graphics w/ WebGL" pages
// 181-183
mat4 rotationY(in float angle) {
  return mat4(cos(angle), 0, sin(angle), 0, 0, 1.0, 0, 0, -sin(angle), 0,
              cos(angle), 0, 0, 0, 0, 1);
}

mat4 rotationX(in float angle) {
  return mat4(1, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle),
              cos(angle), 0, 0, 0, 0, 1);
}

void main() {
  mat4 rotationMatrix = rotationY(radians(rotationDegrees));
  mat4 rotatedModel = model * rotationMatrix;
  gl_Position = projection * view * rotatedModel * vec4(aPos, 1.0);
  inColor = aColor;
}
