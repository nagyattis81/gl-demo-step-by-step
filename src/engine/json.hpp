#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

using namespace std;
using namespace glm;

namespace jsonxx {
class Object;
class Array;
} // namespace jsonxx

namespace JSON {
void ivec2ToObject(const ivec2 &value, const string &name,
                   jsonxx::Object &object);
void ObjectToivec2(ivec2 &value, const string &name,
                   const jsonxx::Object &object);
void vec3ToArray(const vec3 &value, jsonxx::Array &array);
void ArrayTovec3(vec3 &value, const jsonxx::Array &array);
void floatToArray(const float value, jsonxx::Array &array);
void ArrayTofloat(float &value, const jsonxx::Array &array);

jsonxx::Object *Load(const char *fileName);
void Save(const char *fileName, const jsonxx::Object &object);
} // namespace JSON