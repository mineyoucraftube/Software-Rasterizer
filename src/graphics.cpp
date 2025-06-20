#include "graphics.h"

// #define pperpendicular(a) float2((a).y, -(a).x)

float graphics::dot(float2 a, float2 b) {
  return (a.x * b.x) + (a.y * b.y);
}
float2 graphics::perpendicular(float2 a) {
  return float2(a.y, -a.x);
}
bool graphics::PointOnRightSideOfLine(float2 a, float2 b, float2 p) {
  return (dot(p - a, perpendicular(b - a)) > 0);
}

bool graphics::PointInTriangle(triangle2 trig, float2 p) {
  // bool ab = PointOnRightSideOfLine(trig.a, trig.b, p);
  bool bc = PointOnRightSideOfLine(trig.b, trig.c, p);
  // bool ca = PointOnRightSideOfLine(trig.c, trig.a, p);
  //  if (ab && bc && ca);
  //   throw("a");
  // return ab == bc && bc == ca;
  // return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
  return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
}

float2 graphics::WorldToScreen(float3 a, int x, int y) {
  float screenHeight_world = 6;
  float pixelsPerWorldUnit = y / screenHeight_world;

  float2 pixelOffset = float2(a.x, a.y) * pixelsPerWorldUnit;
  return float2(x, y) / 2 + pixelOffset;
}
#define SCREENSPACE_RANGE 3

void graphics::render(simple_object* cube, Image* image) {
  float screenposFx;
  float screenposFy;
  triangle curtri;
  for (int i = 0; i < cube->num_triangle; i++) {
    curtri = cube->tri[i];
    // if (cube.tri[i].n.z > 0) {
    if (curtri.n.z > 0) {
      triangle2 trig;

      trig.a = WorldToScreen(curtri.v.a, image->x, image->y);
      trig.b = WorldToScreen(curtri.v.b, image->x, image->y);
      trig.c = WorldToScreen(curtri.v.c, image->x, image->y);

      float iminx = math::clamp(mmin(mmin(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float iminy = math::clamp(mmin(mmin(trig.a.y, trig.b.y), trig.c.y), 0, image->y);
      float imaxx = math::clamp(mmax(mmax(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float imaxy = math::clamp(mmax(mmax(trig.a.y, trig.b.y), trig.c.y), 0, image->y);
      
      //float minx = math::clamp(mmin(mmin(curtri.v.a.x, curtri.v.b.x), curtri.v.c.x), -SCREENSPACE_RANGE, SCREENSPACE_RANGE);
      //float miny = math::clamp(mmin(mmin(curtri.v.a.y, curtri.v.b.y), curtri.v.c.y), -SCREENSPACE_RANGE, SCREENSPACE_RANGE);
      //float maxx = math::clamp(mmax(mmax(curtri.v.a.x, curtri.v.b.x), curtri.v.c.x), -SCREENSPACE_RANGE, SCREENSPACE_RANGE);
      //float maxy = math::clamp(mmax(mmax(curtri.v.a.y, curtri.v.b.y), curtri.v.c.y), -SCREENSPACE_RANGE, SCREENSPACE_RANGE);

      //int j_max = mmap(maxx, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, image->x) + 1;
      //int k_max = mmap(maxy, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, image->y) + 1;
      //for (int j = mmap(minx, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, image->x); j < j_max; j++) {
      //  for (int k = mmap(miny, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, image->y); k < k_max; k++) {
      for (int j = iminx; j < imaxx; j++) {
        for (int k = iminy; k < imaxy; k++) {
          screenposFx = (j * 0.005859375) - 3;
          screenposFy = (k * 0.005859375) - 3;
          screenposFx = mmap(j, 0, image->x, -SCREENSPACE_RANGE, SCREENSPACE_RANGE);
          screenposFy = mmap(k, 0, image->y, -SCREENSPACE_RANGE, SCREENSPACE_RANGE);
          //if (PointInTriangle(curtri.v, float2(screenposFx, screenposFy))) {
          if (PointInTriangle(trig, float2(j, k))) {
            image->pixels[j][k].r = curtri.color.x * 255;  // * math::max(0, curtri.n.y);
            image->pixels[j][k].g = curtri.color.y;        // * math::max(0, curtri.n.y);
            image->pixels[j][k].b = curtri.color.z;        // * math::max(0, curtri.n.y);
            // image->pixels[j][k] = curtri.color;  // * math::max(0, curtri.n.y);
          }
        }
      }
    }
  }
}
