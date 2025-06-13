#pragma once
// #include <vector>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "graphics.h"

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
  int verti;
  int uvi;
  int normali;
};

struct raw_object {
  const size_t num_vertice;
  float3* verts;
  const size_t num_normal;
  float3* normals;
  const size_t num_uv;
  float2* uvs;
  const size_t num_face;
  face* faces;

  raw_object(const int v, const size_t n, const size_t t, const size_t f) : num_vertice(v), num_normal(n), num_uv(t), num_face(f) {
    verts = new float3[num_vertice];
    normals = new float3[num_normal];
    uvs = new float2[num_uv];
    faces = new face[num_face];
  }
};

class objparser {
 private:
 public:
  raw_object parse(const char* filename);
};