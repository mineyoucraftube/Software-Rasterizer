#pragma once
// #include <vector>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "graphics.h"
#include "math.h"

struct indexing {
  size_t file_index = 0;
  const size_t file_size;
  size_t v = 0;
  size_t n = 0;
  size_t t = 0;
  size_t f = 0;
  indexing(const size_t size) : file_size(size) {}
};

struct face {
  const int num_vert;
  int* verti;
  int* uvi;
  int* normali;
  face(const int size) : num_vert(size) {
    verti = new int[num_vert];
    uvi = new int[num_vert];
    normali = new int[num_vert];
  }
};

struct obj_object {
  const size_t num_vertice;
  const size_t num_normal;
  const size_t num_uv;
  const size_t num_face;
  float3* verts;
  float3* normals;

  float2* uvs;
  face** faces;

  obj_object(const int v, const size_t n, const size_t t, const size_t f) : num_vertice(v), num_normal(n), num_uv(t), num_face(f) {
    verts = new float3[num_vertice];
    normals = new float3[num_normal];
    uvs = new float2[num_uv];
    faces = new face*[num_face];
  }
};

class objparser {
 private:
  obj_object get_obj_params(char* file, size_t size);
  float parsefloat(char* file, indexing* index);
  int parseint(char* file, indexing* index);
  void parsevert(char* file, obj_object object, indexing* index);
  void parsenormal(char* file, obj_object object, indexing* index);
  void parseUV(char* file, obj_object object, indexing* index);
  void parseface(char* file, obj_object object, indexing* index);
  void parseline(char* file, obj_object object, indexing* index);

 public:
  obj_object parse(const char* filename);
    simple_object rawObjToSimpleObj(obj_object rawobj);

};