#include "spdlog/spdlog.h"

#include "parameters.hpp"
#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <jsonxx.h>

using namespace std;

struct Parameter {
  const char *name = nullptr;
  virtual void GUI() = 0;
  virtual void Save(jsonxx::Array &array) = 0;
  virtual bool Load(const jsonxx::Array &array) = 0;
};

struct Vec3 : public Parameter {
  vec3 *value = nullptr;
  void GUI() override { ImGui::DragFloat3(name, &value->x); }
  void Save(jsonxx::Array &array) override {
    array << value->x;
    array << value->y;
    array << value->z;
  }
  bool Load(const jsonxx::Array &array) override {
    if (array.size() != 3)
      return false;
    value->x = static_cast<float>(array.get<jsonxx::Number>(0));
    value->y = static_cast<float>(array.get<jsonxx::Number>(1));
    value->z = static_cast<float>(array.get<jsonxx::Number>(2));
    return true;
  }
};

struct Color3 : public Vec3 {
  void GUI() override { ImGui::ColorEdit3(name, &value->r); }
};

struct Bool : public Parameter {
  bool *value = nullptr;
  void GUI() override { ImGui::Checkbox(name, value); }
  void Save(jsonxx::Array &array) override { array << *value; }
  bool Load(const jsonxx::Array &array) override {
    if (array.size() != 1)
      return false;
    *value = array.get<jsonxx::Boolean>(0);
    return true;
  }
};

struct Float : public Parameter {
  float *value = nullptr;
  float v_speed = 1.0f;
  float v_min = 0.0f;
  float v_max = 0.0f;
  const char *format = "%.3f";
  void GUI() override {
    ImGui::DragFloat(name, value, v_speed, v_min, v_max, format,
                     ImGuiSliderFlags_AlwaysClamp);
  }
  void Save(jsonxx::Array &array) override { array << *value; }
  bool Load(const jsonxx::Array &array) override {
    if (array.size() != 1)
      return false;
    *value = static_cast<float>(array.get<jsonxx::Number>(0));
    return true;
  }
};

bool Parameters::Load(const char *name) {
  const string fileName = "data/parameters/" + string(name) + ".json";
  spdlog::info("*** Load {}", fileName);

  ifstream file(fileName);
  std::string str((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  jsonxx::Object object;
  if (!object.parse(str))
    return false;

  if (object.has<jsonxx::Array>("parameters")) {
    const jsonxx::Array &array = object.get<jsonxx::Array>("parameters");
    for (unsigned int i = 0; i < array.size(); i++) {
      const jsonxx::Object &itemObject = array.get<jsonxx::Object>(i);
      if (!itemObject.has<jsonxx::String>("name") &&
          !itemObject.has<jsonxx::String>("value"))
        continue;
      const string name = itemObject.get<jsonxx::String>("name");
      for (auto it : items) {
        if (it->name == name) {
          if (!it->Load(itemObject.get<jsonxx::Array>("value")))
            return false;
          break;
        }
      }
    }
  }

  if (object.has<jsonxx::Array>("children")) {
    // TODO
  }

  return true;
}

void Parameters::Save(const char *name) {
  filesystem::create_directory("data/parameters/");
  const string fileName = "data/parameters/" + string(name) + ".json";
  spdlog::info("*** Save {}", fileName);

  fstream file;
  file.open(fileName, ios::out);
  if (!file.is_open()) {
    spdlog::critical("open error!");
    return;
  }

  jsonxx::Object object;
  jsonxx::Array parameterArray;
  for (auto it : items) {
    jsonxx::Object itemObject;
    itemObject << "name" << it->name;
    jsonxx::Array itemValueArray;
    it->Save(itemValueArray);
    itemObject << "value" << itemValueArray;
    parameterArray << itemObject;
  }
  object << "parameters" << parameterArray;

  jsonxx::Array childArray;
  object << "children" << childArray;

  std::string str = object.json();
  file << str;
  file.close();
}

void Parameters::GUI() {
  for (auto it : items)
    it->GUI();
}

template <typename V, typename T>
T *Push(vector<Parameter *> &items, const char *name, V *value) {
  auto parameter = new T();
  parameter->name = name;
  parameter->value = value;
  items.push_back(parameter);
  return parameter;
}

void Parameters::Vec3(const char *name, vec3 *value) {
  Push<vec3, ::Vec3>(items, name, value);
}

void Parameters::Color3(const char *name, vec3 *value) {
  Push<vec3, ::Color3>(items, name, value);
}

void Parameters::Bool(const char *name, bool *value) {
  Push<bool, ::Bool>(items, name, value);
}

void Parameters::Float(const char *name, float *value, const float v_speed,
                       const float v_min, const float v_max,
                       const char *format) {
  ::Float *parameter = Push<float, ::Float>(items, name, value);
  parameter->v_speed = v_speed;
  parameter->v_min = v_min;
  parameter->v_max = v_max;
  parameter->format = format;
}