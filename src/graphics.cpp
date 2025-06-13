#include "graphics.h"

float graphics::dot(float2 a, float2 b) {
  return (a.x * b.x) + (a.y * b.y);
}
float2 graphics::perpendicular(float2 a) {

  return float2(a.y, -a.x);
}
bool graphics::PointOnRightSideOfLine(float2 a, float2 b, float2 p){
  if(dot(p-a, perpendicular(b-a))>0)
  return 1;
  return 0;
}

bool graphics::PointInTriangle(triangle2 trig, float2 p){
  bool ab = PointOnRightSideOfLine(trig.a, trig.b, p);
  bool bc = PointOnRightSideOfLine(trig.b, trig.c, p);
  bool ca = PointOnRightSideOfLine(trig.c, trig.a, p);
  return ab && bc && ca;
}