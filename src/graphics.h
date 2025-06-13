#pragma once
#include "typedef.h"

struct float2 {
  float x;
  float y;

  float2(float x = 0, float y = 0) : x(x), y(y) {}

  float2 operator+(const float2& a) {
    return float2(x + a.x, y + a.y);
  }

  float2 operator-(const float2& a) {
    return float2(x - a.x, y - a.y);
  }

  float2 operator*(const float2& a) {
    return float2(x * a.x, y * a.y);
  }

  float2 operator/(const float2& a) {
    return float2(x / a.x, y / a.y);
  }
};

struct float3 {
  float x;
  float y;
  float z;
};
struct triangle2 {
  float2 a;
  float2 b;
  float2 c;
};
struct triangle3 {
  float3 a;
  float3 b;
  float3 c;
};

struct object {
  int num_vertice;
  int num_triangle;
  
};

class graphics {
 private:
 public:
  float dot(float2 a, float2 b);
  float2 perpendicular(float2 a);
  bool PointOnRightSideOfLine(float2 a, float2 b, float2 p);
  bool PointInTriangle(triangle2 trig, float2 p);
};
