#pragma once
#include <cstddef>
#include "math.h"
#include "typedef.h"
#include "number.h"
#define image_x 100
#define image_y 75
struct triangle3 {
  float3 a;
  float3 b;
  float3 c;
  triangle3(float3 a = 0, float3 b = 0, float3 c = 0) : a(a), b(b), c(c) {}
};
struct triangle2 {
  float2 a;
  float2 b;
  float2 c;

  triangle2(float2 a = 0, float2 b = 0, float2 c = 0) : a(a), b(b), c(c) {}
  triangle2(triangle3 a) : a(a.a.x, a.a.y), b(a.b.x, a.b.y), c(a.c.x, a.c.y) {}
};

struct triangle {
  triangle3 v;
  float3 n;
  triangle2 uv;
  float3 color;
};

struct simple_object {
  const size_t num_triangle;
  triangle* tri;

  simple_object(const int f) : num_triangle(f) {
    tri = new triangle[num_triangle];
  }
};

struct Image {
  int x = image_x;
  int y = image_y;
  float3 pixels[image_x][image_y];
};

class graphics {
 private:
 public:
  float dot(float2 a, float2 b);
  float2 perpendicular(float2 a);
  bool PointOnRightSideOfLine(float2 a, float2 b, float2 p);
  bool PointInTriangle(triangle2 trig, float2 p);
  float2 WorldToScreen(float3 a, int x, int y);

  void render(simple_object* cube, Image* image);
};
