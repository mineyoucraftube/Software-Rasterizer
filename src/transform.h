#include "math.h"

struct matrix3{
  float3 ihat;
  float3 jhat;
  float3 khat;
  matrix3(){

  }
  matrix3(float3 rotation);
  matrix3 operator*(const matrix3& a);
};


class transform {
 private:
 public:
 static float3 toworldpoint(float3 p, float3 rot, float3 tra = 0);
};
