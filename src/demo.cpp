#include "spdlog/spdlog.h"

#include "demo.hpp"
#include "part.hpp"

extern Part *CreatePart01();
extern Part *CreatePart02();

std::map<double, Part *> Demo::CreateParts() {
  std::map<double, Part *> parts;
  parts[9.0] = CreatePart01();
  parts[20.0] = CreatePart02();
  return parts;
}

bool Demo::Init() {
  if (!logo.Load({.fileName = "data/textures/cover_1.jpg", .flip = false}))
    return false;
  if (!fade.Init())
    return false;
  fade.Add(0.0, 1.0, 0.0f, 1.0f);
  fade.Add(8.0, 9.0, 1.0f, 0.0f);
  fade.Add(9.0, 10.0, 0.0f, 1.0f);
  fade.Add(19.0, 20.0, 1.0f, 0.0f);
  return true;
}

void Demo::Render(const double time) { fade.Render(time); }
