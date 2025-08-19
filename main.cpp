#include <iostream>
#include "src/transform.h"

void sc(int col){
std::cout << "\033[16H";
}

matrix4 a(float3(0, 3.1415926535897932384626433832795/2, 0), float3(0, 5, 0)), b, c;
//matrix4 a(float3(0, 0, 0), float3(0, 5, 0)), b, c;
float4 d(1, 0, 0, 1), e, f;

void printmatrix(matrix4 mat){
  std::cout << mat.ihat.x << "\033[17G" << mat.jhat.x << "\033[33G" << mat.khat.x << "\033[49G" << mat.lhat.x << "\n";
  std::cout << mat.ihat.y << "\033[17G" << mat.jhat.y << "\033[33G" << mat.khat.y << "\033[49G" << mat.lhat.y << "\n";
  std::cout << mat.ihat.z << "\033[17G" << mat.jhat.z << "\033[33G" << mat.khat.z << "\033[49G" << mat.lhat.z << "\n";
  std::cout << mat.ihat.w << "\033[17G" << mat.jhat.w << "\033[33G" << mat.khat.w << "\033[49G" << mat.lhat.w << "\n";
}

void printparsematrix(matrix4 mat){
  std::cout  << "{{" << mat.ihat.x << "," << mat.jhat.x << "," << mat.khat.x << "," << mat.lhat.x
            << "},{" << mat.ihat.y << "," << mat.jhat.y << "," << mat.khat.y << "," << mat.lhat.y
            << "},{" << mat.ihat.z << "," << mat.jhat.z << "," << mat.khat.z << "," << mat.lhat.z
            << "},{" << mat.ihat.w << "," << mat.jhat.w << "," << mat.khat.w << "," << mat.lhat.w
            << "}}\n";
}

void printvector(float4 a){
  std::cout << a.x << "\033[17G" << a.y << "\033[33G" << a.z << "\033[49G" << a.w << "\n";
}

void printparsevector(float4 a){
  std::cout << "("<< a.x << "," << a.y << "," << a.z << "," << a.w << ")\n";
}

int main(){
  printmatrix(a);
  std::cout << "\n";
  printvector(d);
  std::cout << "\n";
  //e = transform::transformvector(a, d);
  e = d*a;
  printvector(e);
  std::cout << "\n";

  printparsematrix(a);
  std::cout << "\n";
  printparsevector(d);
  std::cout << "\n";
  printparsevector(e);
  std::cout << "\n";
}