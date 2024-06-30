#pragma once

#include <glm/vec3.hpp>
#include <vector>

using namespace std;
using namespace glm;

struct Parameter;
class Parameters {
private:
  vector<Parameter *> items;

public:
  bool Load(const char *name);
  void Save(const char *name);
  void GUI();
  void Vec3(const char *name, vec3 *value);
  void Color3(const char *name, vec3 *value);
  void Bool(const char *name, bool *value);
  void Float(const char *name, float *value, const float v_speed = 1.0f,
             const float v_min = 0.0f, const float v_max = 0.0f,
             const char *format = "%.3f");
};
