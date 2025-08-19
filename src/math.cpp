#include "math.h"

float2::float2(float x) : x(x), y(x) {}
float2::float2(float x, float y) : x(x), y(y) {}
float2 float2::operator+(const float2& a) {
  return float2(x + a.x, y + a.y);
}

float2 float2::operator-(const float2& a) {
  return float2(x - a.x, y - a.y);
}

float2 float2::operator*(const float2& a) {
  return float2(x * a.x, y * a.y);
}

float2 float2::operator/(const float2& a) {
  return float2(x / a.x, y / a.y);
}

float3::float3(float x, float y, float z) : x(x), y(y), z(z) {}
float3::float3(float x) : x(x), y(x), z(x) {}

float3 float3::operator+(const float3& a) {
  return float3(x + a.x, y + a.y, z + a.z);
}

float3 float3::operator+=(const float3& a) {
  return float3(x += a.x, y += a.y, z += a.z);
}

float3 float3::operator-(const float3& a) {
  return float3(x - a.x, y - a.y, z - a.z);
}

float3 float3::operator*(const float3& a) {
  return float3(x * a.x, y * a.y, z * a.z);
}
float3 float3::operator*(const float& a) {
  return float3(x * a, y * a, z * a);
}

float3 float3::operator/(const float3& a) {
  return float3(x / a.x, y / a.y, z / a.z);
}

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
float4::float4(float x) : x(x), y(x), z(x) {}

float4 float4::operator+(const float4& a) {
  return float4(x + a.x, y + a.y, z + a.z, w + a.w);
}

float4 float4::operator+=(const float4& a) {
  return float4(x += a.x, y += a.y, z += a.z, w += a.w);
}

float4 float4::operator-(const float4& a) {
  return float4(x - a.x, y - a.y, z - a.z, w - a.w);
}

float4 float4::operator*(const float4& a) {
  return float4(x * a.x, y * a.y, z * a.z, w * a.w);
}
float4 float4::operator*(const float& a) {
  return float4(x * a, y * a, z * a, w * a);
}
// float4 operator*(const matrix4& a){
//   return (a.ihat * x) + (a.jhat * y) + (a.khat * z) + (a.lhat * w);
// }

float4 float4::operator/(const float4& a) {
  return float4(x / a.x, y / a.y, z / a.z, w / a.w);
}

int2::int2(int x) : x(x), y(x) {}
int2::int2(int x, int y) : x(x), y(y) {}

int2 int2::operator+(const int2& a) {
  return int2(x + a.x, y + a.y);
}

int2 int2::operator-(const int2& a) {
  return int2(x - a.x, y - a.y);
}

int2 int2::operator*(const int2& a) {
  return int2(x * a.x, y * a.y);
}

int2 int2::operator/(const int2& a) {
  return int2(x / a.x, y / a.y);
}

int3::int3(float x, float y, float z) : x(x), y(y), z(z) {}
int3::int3(float x) : x(x), y(x), z(x) {}

int3 int3::operator+(const int3& a) {
  return int3(x + a.x, y + a.y, z + a.z);
}

int3 int3::operator-(const int3& a) {
  return int3(x - a.x, y - a.y, z - a.z);
}

int3 int3::operator*(const int3& a) {
  return int3(x * a.x, y * a.y, z * a.z);
}
int3 int3::operator/(const int3& a) {
  return int3(x / a.x, y / a.y, z / a.z);
}

float math::min(float a, float b) {
  if (a < b)
    return a;
  return b;
}

float2 math::min(float2 a, float2 b) {
  return float2((a.x < b.x) ? a.x : b.x, (a.y < b.y) ? a.y : b.y);
}

float math::max(float a, float b) {
  if (a > b)
    return a;
  return b;
}

float2 math::max(float2 a, float2 b) {
  return float2((a.x > b.x) ? a.x : b.x, (a.y > b.y) ? a.y : b.y);
}

float math::clamp(float x, float low, float high) {
  return max(low, min(x, high));
}

float2 math::clamp(float2 x, float2 low, float2 high) {
  return float2(max(low.x, min(x.x, high.x)), max(low.y, min(x.y, high.y)));
}

float math::exponent(float a, int b) {
  float c = 1;
  for (; b > 0; b--) {
    c *= a;
  }
  for (; b < 0; b++) {
    c /= a;
  }
  return c;
}

float math::map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float2 math::map(float2 x, float2 in_min, float2 in_max, float2 out_min, float2 out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
