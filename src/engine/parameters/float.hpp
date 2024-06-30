
#pragma once

#include "parameter.hpp"

struct Float : public Parameters::Parameter {
  float *value = nullptr;
  float v_speed = 1.0f;
  float v_min = 0.0f;
  float v_max = 0.0f;
  const char *format = "%.3f";
  void GUI() override;
  void Save(jsonxx::Array &array) override;
  bool Load(const jsonxx::Array &array) override;
};