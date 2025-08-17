#pragma once
#include <math.h>
#include <algorithm>
#define mmin(a, b) ((a) < (b) ? (a) : (b))
#define mmax(a, b) ((a) > (b) ? (a) : (b))
#define mmap(x, in_min, in_max, out_min, out_max) (float(((x) - (in_min)) * ((out_max) - (out_min))) / ((in_max) - (in_min)) + (out_min))

//struct float3;

struct float2 {
  float x;
  float y;

  float2(float x = 0) : x(x), y(x) {}
  float2(float x, float y) : x(x), y(y) {}
  //float2(float3 a);
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
  float3(float x, float y, float z) : x(x), y(y), z(z) {}
  float3(float x = 0) : x(x), y(x), z(x) {}

  float3 operator+(const float3& a) {
    return float3(x + a.x, y + a.y, z + a.z);
  }

  float3 operator+=(const float3& a) {
    return float3(x += a.x, y += a.y, z += a.z);
  }

  float3 operator-(const float3& a) {
    return float3(x - a.x, y - a.y, z - a.z);
  }

  float3 operator*(const float3& a) {
    return float3(x * a.x, y * a.y, z * a.z);
  }
  float3 operator*(const float& a) {
    return float3(x * a, y * a, z * a);
  }

  float3 operator/(const float3& a) {
    return float3(x / a.x, y / a.y, z / a.z);
  }
};

struct float4 {
  float x;
  float y;
  float z;
  float w;
  float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
  float4(float x = 0) : x(x), y(x), z(x) {}

  float4 operator+(const float4& a) {
    return float4(x + a.x, y + a.y, z + a.z, w + a.w);
  }

  float4 operator+=(const float4& a) {
    return float4(x += a.x, y += a.y, z += a.z, w += a.w);
  }

  float4 operator-(const float4& a) {
    return float4(x - a.x, y - a.y, z - a.z, w - a.w);
  }

  float4 operator*(const float4& a) {
    return float4(x * a.x, y * a.y, z * a.z, w * a.w);
  }
  float4 operator*(const float& a) {
    return float4(x * a, y * a, z * a, w * a);
  }

  float4 operator/(const float4& a) {
    return float4(x / a.x, y / a.y, z / a.z, w / a.w);
  }
};

struct int2{
  int x;
  int y;

  int2(int x = 0) : x(x), y(x) {}
  int2(int x, int y) : x(x), y(y) {}
  int2 operator+(const int2& a) {
    return int2(x + a.x, y + a.y);
  }

  int2 operator-(const int2& a) {
    return int2(x - a.x, y - a.y);
  }

  int2 operator*(const int2& a) {
    return int2(x * a.x, y * a.y);
  }

  int2 operator/(const int2& a) {
    return int2(x / a.x, y / a.y);
  }

};

struct int3 {
  float x;
  float y;
  float z;
  int3(float x, float y, float z) : x(x), y(y), z(z) {}
  int3(float x = 0) : x(x), y(x), z(x) {}

  int3 operator+(const int3& a) {
    return int3(x + a.x, y + a.y, z + a.z);
  }

  int3 operator-(const int3& a) {
    return int3(x - a.x, y - a.y, z - a.z);
  }

  int3 operator*(const int3& a) {
    return int3(x * a.x, y * a.y, z * a.z);
  }
  int3 operator/(const int3& a) {
    return int3(x / a.x, y / a.y, z / a.z);
  }
};

class math {
 private:
 public:
  static float min(float a, float b);
  static float2 min(float2 a, float2 b);
  static float max(float a, float b);
  static float2 max(float2 a, float2 b);
  static float clamp(float a, float b, float c);
  static float2 clamp(float2 a, float2 b, float2 c);
  static float exponent(float a, int b);
  static float map(float x, float in_min, float in_max, float out_min, float out_max);
  static float2 map(float2 x, float2 in_min, float2 in_max, float2 out_min, float2 out_max);
};
