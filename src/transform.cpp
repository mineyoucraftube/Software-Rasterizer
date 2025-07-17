#include "transform.h"


void getbasisvectors(float3* ihat, float3* jhat, float3* khat, float yaw){
  *ihat = float3(cos(yaw), 0, -sin(yaw));
  *jhat = float3(0, 1, 0);
  *khat = float3(sin(yaw), 0, cos(yaw));
}

float3 transformvector(float3 ihat, float3 jhat, float3 khat, float3 v){
  return (ihat * v.x) + (jhat * v.y) + (khat * v.z);
}

float3 transform::toworldpoint(float3 p, float yaw) {
  float3 ihat, jhat, khat;
  getbasisvectors(&ihat, &jhat, &khat, yaw);
  return transformvector(ihat, jhat, khat, p);
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