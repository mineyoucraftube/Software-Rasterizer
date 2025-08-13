#include "transform.h"

matrix3::matrix3(float3 rotation) {
  /*  
  matrix3 y, p, r, yp;
  y.ihat = float3(cos(rotation.y) , 0          , -sin(rotation.y));
  y.jhat = float3(0          , 1          , 0          );
  y.khat = float3(sin(rotation.y) , 0          , cos(rotation.y) );

  p.ihat = float3(1          , 0          , 0          );
  p.jhat = float3(0          , cos(rotation.x) , -sin(rotation.x));
  p.khat = float3(0          , sin(rotation.x) , cos(rotation.x) );
  
  r.ihat = float3(cos(rotation.z) , -sin(rotation.z), 0          );
  r.jhat = float3(sin(rotation.z) , cos(rotation.z) , 0          );
  r.khat = float3(0          , 0          , 1          );
  
  yp.ihat = (y.ihat *  p.ihat.x) + ( y.jhat *  p.ihat.y) + ( y.khat *  p.ihat.z);
  yp.jhat = (y.ihat *  p.jhat.x) + ( y.jhat *  p.jhat.y) + ( y.khat *  p.jhat.z);
  yp.khat = (y.ihat *  p.khat.x) + ( y.jhat *  p.khat.y) + ( y.khat *  p.khat.z);

  ihat = (yp.ihat *  r.ihat.x) + ( yp.jhat *  r.ihat.y) + ( yp.khat *  r.ihat.z);
  jhat = (yp.ihat *  r.jhat.x) + ( yp.jhat *  r.jhat.y) + ( yp.khat *  r.jhat.z);
  khat = (yp.ihat *  r.khat.x) + ( yp.jhat *  r.khat.y) + ( yp.khat *  r.khat.z);*/
  float sx = sin(rotation.x);
  float sy = sin(rotation.y);
  float sz = sin(rotation.z);
  float cx = cos(rotation.x);
  float cy = cos(rotation.y);
  float cz = cos(rotation.z);
  
  ihat = float3((cy * cz) + (sy *-sx *-sz), cx *-sz, (-sy * cz) + (cy *-sx *-sz));
  jhat = float3((cy * sz) + (sy *-sx * cz), cx * cz, (-sy * sz) + (cy *-sx * cz));
  khat = float3( sy * cx                  , sx     , cy * cx);


}

matrix3 matrix3::operator*(const matrix3& a) {
  matrix3 mat;
  mat.ihat = (ihat *  a.ihat.x) + ( jhat *  a.ihat.y) + ( khat *  a.ihat.z);
  mat.jhat = (ihat *  a.jhat.x) + ( jhat *  a.jhat.y) + ( khat *  a.jhat.z);
  mat.khat = (ihat *  a.khat.x) + ( jhat *  a.khat.y) + ( khat *  a.khat.z);
  return mat;
}

float3 transformvector(float3 ihat, float3 jhat, float3 khat, float3 v){
  return (ihat * v.x) + (jhat * v.y) + (khat * v.z);
}
float3 transformvector(matrix3 mat, float3 v){
  return (mat.ihat * v.x) + (mat.jhat * v.y) + (mat.khat * v.z);
}

void getbasisvectors(float3* ihat, float3* jhat, float3* khat, float3 rot){
  matrix3 y, p, r, yp;
  y.ihat = float3(cos(rot.y), 0         ,-sin(rot.y));
  y.jhat = float3(0         , 1         , 0         );
  y.khat = float3(sin(rot.y), 0         , cos(rot.y));

  p.ihat = float3(1         , 0         , 0         );
  p.jhat = float3(0         , cos(rot.x),-sin(rot.x));
  p.khat = float3(0         , sin(rot.x), cos(rot.x));
  
  r.ihat = float3(cos(rot.z),-sin(rot.z), 0         );
  r.jhat = float3(sin(rot.z), cos(rot.z), 0         );
  r.khat = float3(0         , 0         , 1         );
  
  yp.ihat = transformvector(y.ihat, y.jhat, y.khat, p.ihat);
  yp.jhat = transformvector(y.ihat, y.jhat, y.khat, p.jhat);
  yp.khat = transformvector(y.ihat, y.jhat, y.khat, p.khat);

  *ihat = transformvector(yp.ihat, yp.jhat, yp.khat, r.ihat);
  *jhat = transformvector(yp.ihat, yp.jhat, yp.khat, r.jhat);
  *khat = transformvector(yp.ihat, yp.jhat, yp.khat, r.khat);
}


float3 transform::toworldpoint(float3 p, float3 rot, float3 tra) {
  //float3 ihat, jhat, khat;
  //getbasisvectors(&ihat, &jhat, &khat, rot);
  //return transformvector(ihat, jhat, khat, p);
  matrix3 mat(rot);
  return transformvector(mat, p)+tra;
}

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
*/