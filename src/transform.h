#include "math.h"

struct matrix4{
  float4 ihat;
  float4 jhat;
  float4 khat;
  float4 lhat;
  matrix4(){

  }
  matrix4(float3 rotation, float3 translation);
  matrix4 operator*(const matrix4& a);
};


class transform {
 private:
 public:
 static float3 toworldpoint(float3 p, float3 rot, float3 tra = 0);
};
