#include "graphics.h"
// #define pperpendicular(a) float2((a).y, -(a).x)

float graphics::dot(float2 a, float2 b) {
  return (a.x * b.x) + (a.y * b.y);
}
float2 graphics::perpendicular(float2 a) {
  return float2(a.y, -a.x);
}
bool graphics::PointOnRightSideOfLine(float2 a, float2 b, float2 p) {
  return dot(p - a, perpendicular(b - a)) >= 0;
}

float distance(float2 a, float2 b){
  return sqrt(((b-a).x*(b-a).x)+((b-a).y*(b-a).y));
}

bool graphics::PointInTriangle(triangle2 trig, float2 p) {
  //bool ab = PointOnRightSideOfLine(trig.a, trig.b, p);
  bool bc = PointOnRightSideOfLine(trig.b, trig.c, p);
  //bool ca = PointOnRightSideOfLine(trig.c, trig.a, p);
  //  if (ab && bc && ca);
  //   throw("a");
  //return ab == bc && bc == ca;
  //return ab && bc && ca;
  // return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
  return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
  //return !PointOnRightSideOfLine(trig.a, trig.b, p) && !PointOnRightSideOfLine(trig.b, trig.c, p) && !PointOnRightSideOfLine(trig.c, trig.a, p);
  //return PointOnRightSideOfLine(trig.a, trig.b, p) && PointOnRightSideOfLine(trig.b, trig.c, p) && PointOnRightSideOfLine(trig.c, trig.a, p);
}

float testdot(float2 a, float2 b) {
  return (a.x * b.x) + (a.y * b.y);
}
float2 testperpendicular(float2 a) {
  return float2(a.y, -a.x);
}
float testPointOnRightSideOfLine(float2 a, float2 b, float2 p) {
  return testdot(p - a, testperpendicular(b - a))>0;
}

bool testPointInTriangle(triangle2 trig, float2 p) {
  //bool ab = testPointOnRightSideOfLine(trig.a, trig.b, p);
  //bool bc = testPointOnRightSideOfLine(trig.b, trig.c, p);
  //bool ca = testPointOnRightSideOfLine(trig.c, trig.a, p);
  //  if (ab && bc && ca);
  //   throw("a");
  //return ab == bc && bc == ca;
  //return ab && bc && ca;
  // return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
  //return PointOnRightSideOfLine(trig.a, trig.b, p) == bc && bc == PointOnRightSideOfLine(trig.c, trig.a, p);
  //return !PointOnRightSideOfLine(trig.a, trig.b, p) && !PointOnRightSideOfLine(trig.b, trig.c, p) && !PointOnRightSideOfLine(trig.c, trig.a, p);
  return testPointOnRightSideOfLine(trig.a, trig.b, p) && testPointOnRightSideOfLine(trig.b, trig.c, p) && testPointOnRightSideOfLine(trig.c, trig.a, p);
}


float2 VertexToScreen(float3 a, int x = 1024, int y = 1024) {
  /*float screenHeight_world = 2;
  float pixelsPerWorldUnit = y / screenHeight_world;

  float2 pixelOffset = float2(a.x, a.y) * pixelsPerWorldUnit;
  return float2(x, y) / 2 + pixelOffset;*/

  // return float2(x, y) / 2 + (float2(a.x, a.y) * (y / 6.0f));              // 25153
  // return ((float2(x, y) * 3) + (float2(a.x, a.y) * y)) / 6;               // 25618
  // return float2(x / 2 + (a.x * (y / 6.0f)), y / 2 + (a.y * (y / 6.0f)));  // 24980
  // return float2(((x * 3) + (a.x * y)) / 6, ((y * 3) + (a.y * y)) / 6);    // 25198

  // return float2(x, y) / 2 + float2(a.x, a.y) * y / 6;           // 25230
  // return (float2(x, y) * 3 + float2(a.x, a.y) * y) / 6;         // 25130
  // return float2(x / 2 + a.x * y / 6, y / 2 + a.y * y / 6);      // 25089
  // return float2((x * 3 + a.x * y) / 6, (y * 3 + a.y * y) / 6);  // 25276

    return float2(x / 2 + (a.x * (y / 3.0f)), y / 2 + (a.y * (y / 3.0f)));  // 24980
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

triangle yaw_trig(triangle trig, float3 rot){
  triangle *temptrig;
  temptrig = new triangle;

  temptrig->v.a = transform::toworldpoint(trig.v.a, rot);
  temptrig->v.b = transform::toworldpoint(trig.v.b, rot);
  temptrig->v.c = transform::toworldpoint(trig.v.c, rot);
  temptrig->n = transform::toworldpoint(trig.n, rot);


/*
  temptrig->v.a.x = trig.v.a.x * cos(yaw)   + trig.v.a.y * 0    + trig.v.a.z * sin(yaw) ;
  temptrig->v.a.y = trig.v.a.x * 0          + trig.v.a.y * 1    + trig.v.a.z * 0        ;
  temptrig->v.a.z = trig.v.a.x * -sin(yaw)  + trig.v.a.y * 0    + trig.v.a.z * cos(yaw) ;
  
  temptrig->v.b.x = trig.v.b.x * cos(yaw)   + trig.v.b.y * 0    + trig.v.b.z * sin(yaw) ;
  temptrig->v.b.y = trig.v.b.x * 0          + trig.v.b.y * 1    + trig.v.b.z * 0        ;
  temptrig->v.b.z = trig.v.b.x * -sin(yaw)  + trig.v.b.y * 0    + trig.v.b.z * cos(yaw) ;
  
  temptrig->v.c.x = trig.v.c.x * cos(yaw)   + trig.v.c.y * 0    + trig.v.c.z * sin(yaw) ;
  temptrig->v.c.y = trig.v.c.x * 0          + trig.v.c.y * 1    + trig.v.c.z * 0        ;
  temptrig->v.c.z = trig.v.c.x * -sin(yaw)  + trig.v.c.y * 0    + trig.v.c.z * cos(yaw) ;
  
  temptrig->n.x = trig.n.x * cos(yaw)   + trig.n.y * 0    + trig.n.z * sin(yaw) ;
  temptrig->n.y = trig.n.x * 0          + trig.n.y * 1    + trig.n.z * 0        ;
  temptrig->n.z = trig.n.x * -sin(yaw)  + trig.n.y * 0    + trig.n.z * cos(yaw) ;

  //std::cout << "trig " << temptrig->v.a.x << " ping " << temping->v.a.x << '\n';
/**/
  return *temptrig;
}

Image zbuf;
float yyy = 0;
void graphics::render(simple_object* cube, Image* image, float3 rot){//, Image* image2, Image* image3) {
  float screenposFx;
  float screenposFy;
  const int y = image->y;
  triangle curtri;
  //for (int i = 0; i < zbuf.x; i++) {
  for (int i = 0; i < 1048576; i++) {
    //for (int j = 0; j < zbuf.y; j++) {
      //zbuf.pixels[i][j] = float3(-100000000, -100000000, -100000000);
      //zbuf.pixels[(i*zbuf.y)+j] = float3(-100000000, -100000000, -100000000);
      zbuf.pixels[i] = float3(-100000000, -100000000, -100000000);
    //}
  }

  for (int i = 0; i < cube->num_triangle; i++) {
    //curtri = cube->tri[i];
    rot.x = 0;
    rot.y = yyy;
    rot.z = 0;
    curtri = yaw_trig(cube->tri[i], rot);
    if (curtri.n.z <= 0) 
    continue;
      triangle2 trig;

      trig.a = WorldToScreen(curtri.v.a, image->x, image->y);
      trig.b = WorldToScreen(curtri.v.b, image->x, image->y);
      trig.c = WorldToScreen(curtri.v.c, image->x, image->y);

      float iminx = math::clamp(mmin(mmin(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float iminy = math::clamp(mmin(mmin(trig.a.y, trig.b.y), trig.c.y), 0, image->y);

      float imaxx = math::clamp(mmax(mmax(trig.a.x, trig.b.x), trig.c.x), 0, image->x);
      float imaxy = math::clamp(mmax(mmax(trig.a.y, trig.b.y), trig.c.y), 0, image->y);

      //int iminx = std::clamp(std::min(std::min(trig.a.x, trig.b.x), trig.c.x), 0.0f, (float)image->x);
      //int iminy = std::clamp(std::min(std::min(trig.a.y, trig.b.y), trig.c.y), 0.0f, (float)image->y);

      //int imaxx = std::clamp(std::max(std::max(trig.a.x, trig.b.x), trig.c.x), 0.0f, (float)image->x)+1;
      //int imaxy = std::clamp(std::max(std::max(trig.a.y, trig.b.y), trig.c.y), 0.0f, (float)image->y)+1;
      int l = 0;
      for (int j = iminx; j < imaxx; j++) {
        for (int k = iminy; k < imaxy; k++) {
          //l = (j*y)+k;
          l = (j*1024)+k;
          if(!(zbuf.pixels[l].x < (curtri.v.a.z + curtri.v.b.z + curtri.v.c.z)))
          //if(!(zbuf.pixels[j][k].x < (curtri.v.a.z + curtri.v.b.z + curtri.v.c.z)))
            continue;
          if (!PointInTriangle(trig, float2(j, k)))//inverted because if true, we >>skip<<, guess why i left this comment...
            continue;
          zbuf.pixels[l].x = curtri.v.a.z + curtri.v.b.z + curtri.v.c.z;
        
          
          //zbuf.pixels[j][k].x = curtri.v.a.z + curtri.v.b.z + curtri.v.c.z;
          // image->pixels[j][k].x = curtri.color.x;
          // image->pixels[j][k].y = curtri.color.y;
          // image->pixels[j][k].z = curtri.color.z;
          image->pixels[l] = (curtri.n+1.0f)/2;//(number::randcoloring[i]);// * math::max(0, curtri.n.y + 1) / 2);  // + (curtri.color * 0.2);
          //image->pixels[j][k] = (curtri.n+1.0f)/2;//(number::randcoloring[i]);// * math::max(0, curtri.n.y + 1) / 2);  // + (curtri.color * 0.2);
          //image2->pixels[j][k] = (cube->tri[i].n+1.0f)/2;//(number::randcoloring[i]);// * math::max(0, curtri.n.y + 1) / 2);  // + (curtri.color * 0.2);
        }
      }
    
  }
    yyy+= 2*3.141592654/500;
  if(yyy > 2*3.141592654) yyy -= 2*3.141592654;

}
