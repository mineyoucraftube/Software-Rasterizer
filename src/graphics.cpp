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

float2 VertexToScreen(float3 a, int x = 1024, int y = 1024) {
  float screenHeight_world = 2;
  float pixelsPerWorldUnit = y / screenHeight_world;

  float2 pixelOffset = float2(a.x, a.y) * pixelsPerWorldUnit;
  return float2(x, y) / 2 + pixelOffset;

  // return float2(x, y) / 2 + (float2(a.x, a.y) * (y / 6.0f));              // 25153
  // return ((float2(x, y) * 3) + (float2(a.x, a.y) * y)) / 6;               // 25618
  // return float2(x / 2 + (a.x * (y / 6.0f)), y / 2 + (a.y * (y / 6.0f)));  // 24980
  // return float2(((x * 3) + (a.x * y)) / 6, ((y * 3) + (a.y * y)) / 6);    // 25198

  // return float2(x, y) / 2 + float2(a.x, a.y) * y / 6;           // 25230
  // return (float2(x, y) * 3 + float2(a.x, a.y) * y) / 6;         // 25130
  // return float2(x / 2 + a.x * y / 6, y / 2 + a.y * y / 6);      // 25089
  // return float2((x * 3 + a.x * y) / 6, (y * 3 + a.y * y) / 6);  // 25276

  //    ////  return float2(x / 2 + (a.x * (y / 6.0f)), y / 2 + (a.y * (y / 6.0f)));  // 24980
  // return float2(x / 2 + a.x * y / 6, y / 2 + a.y * y / 6);              // 25089
  // return (float2(x, y) * 3 + float2(a.x, a.y) * y) / 6;                 // 25130
  // return float2(x, y) / 2 + (float2(a.x, a.y) * (y / 6.0f));            // 25153
  // return float2(((x * 3) + (a.x * y)) / 6, ((y * 3) + (a.y * y)) / 6);  // 25198
  // return float2(x, y) / 2 + float2(a.x, a.y) * y / 6;                   // 25230
  // return float2((x * 3 + a.x * y) / 6, (y * 3 + a.y * y) / 6);          // 25276
  // return ((float2(x, y) * 3) + (float2(a.x, a.y) * y)) / 6;             // 25618
}
float2 graphics::WorldToScreen(float3 a, int x = 1024, int y = 1024) {
  return VertexToScreen(a, x, y);
}

void graphics::render(simple_object* cube, Image* image) {
  float screenposFx;
  float screenposFy;
  triangle curtri;
  for (int i = 0; i < cube->num_triangle; i++) {
    curtri = cube->tri[i];
    if (curtri.n.z > 0) {
      triangle2 trig;

      trig.a = WorldToScreen(curtri.v.a, image->x, image->y);
      trig.b = WorldToScreen(curtri.v.b, image->x, image->y);
      trig.c = WorldToScreen(curtri.v.c, image->x, image->y);

      float iminx = math::clamp(mmin(mmin(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float iminy = math::clamp(mmin(mmin(trig.a.y, trig.b.y), trig.c.y), 0, image->y);

      float imaxx = math::clamp(mmax(mmax(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float imaxy = math::clamp(mmax(mmax(trig.a.y, trig.b.y), trig.c.y), 0, image->y);

      for (int j = iminx; j < imaxx; j++) {
        for (int k = iminy; k < imaxy; k++) {
          if (!PointInTriangle(trig, float2(j, k)))
            continue;
          // image->pixels[j][k].x = curtri.color.x;
          // image->pixels[j][k].y = curtri.color.y;
          // image->pixels[j][k].z = curtri.color.z;
          image->pixels[j][k] = (number::randcoloring[i]);// * math::max(0, curtri.n.y + 1) / 2);  // + (curtri.color * 0.2);
        }
      }
    }
  }
}
