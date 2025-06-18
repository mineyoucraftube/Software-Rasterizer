#include "math.h"


float2::float2(float3 a) : x(a.x), y(a.y) {}

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
float math::clamp(float a, float b, float c) {
  return max(a, min(b, c));
}
float2 math::clamp(float2 a, float2 b, float2 c) {
  return max(a, min(b, c));
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
