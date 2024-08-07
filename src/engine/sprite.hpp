#pragma once

#include "gl/buffers.hpp"
#include "gl/program.hpp"
#include "gl/texture2d.hpp"
#include "gl/vao.hpp"
#include <glm/mat4x4.hpp>

using namespace glm;

struct Camera;

class Sprite {
private:
  Texture2D texture;
  Program program;
  GLint modelViewLocation = -1;
  GLint projectionLocation = -1;
  GLint colorLocation = -1;
  VAO vao;
  VBO vbo;

  bool InitTexture(const Texture2D::Parameters &parameters);
  bool InitProgram();
  bool InitVAO();

public:
  bool Load(const Texture2D::Parameters &parameters);
  void Render(const Camera &camera, const mat4 &modelMatrix,
              const vec4 &color) const;
};