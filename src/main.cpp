#include <chrono>
#include <iostream>
#include "graphics.h"
#include "math.h"
#include "objparser.h"
#include "output.h"
#include "typedef.h"

output out;
Image test_image;
graphics gfx;
float2 test;
float2 testing;
float2 floating;
triangle2 trig[2];

objparser obp;

int main() {
  obj_object testing = obp.parse("suzanne3.obj");
  simple_object cube = obp.rawObjToSimpleObj(testing);
  std::cout << cube.num_triangle << "\n";
  /*  for (int i = 0; i < cube.num_triangle; i++) {
      std::cout << "t[" << i << "] ";
      std::cout << cube.tri[i].v.a.x << "  \t ";
      std::cout << cube.tri[i].v.a.y << "  \t ";
      std::cout << cube.tri[i].v.a.z << "  \t \t ";
      std::cout << cube.tri[i].v.b.x << "  \t ";
      std::cout << cube.tri[i].v.b.y << "  \t ";
      std::cout << cube.tri[i].v.b.z << "  \t \t ";
      std::cout << cube.tri[i].v.c.x << "  \t ";
      std::cout << cube.tri[i].v.c.y << "  \t ";
      std::cout << cube.tri[i].v.c.z << "\n";
    }*/
  /*
    std::cout << "num_vertice: " << testing.num_vertice << '\n';
    std::cout << "num_normal: " << testing.num_normal << '\n';
    std::cout << "num_uv: " << testing.num_uv << '\n';
    std::cout << "num_face: " << testing.num_face << '\n';
    for (int i = 0; i < testing.num_vertice; i++) {
      std::cout << "v[" << i << "]: " << testing.verts[i].x << " " << testing.verts[i].y << " " << testing.verts[i].z << '\n';
    }
    for (int i = 0; i < testing.num_normal; i++) {
      std::cout << "n[" << i << "]: " << testing.normals[i].x << " " << testing.normals[i].y << " " << testing.normals[i].z << '\n';
    }
    for (int i = 0; i < testing.num_uv; i++) {
      std::cout << "t[" << i << "]: " << testing.uvs[i].x << " " << testing.uvs[i].y << '\n';
    }
    for (int i = 0; i < testing.num_face; i++) {
      std::cout << "f[" << i << "]:";
      for (int j = 0; j < testing.faces[i]->num_vert; j++) {
        std::cout << " " << testing.faces[i]->verti[j] << "/" << testing.faces[i]->uvi[j] << "/" << testing.faces[i]->normali[j];
      }
      std::cout << '\n';
    }*/
  /*
    cube.tri[0].v.a = float3(-0.8899375528192, -0.1466161955218, 1);
    cube.tri[0].v.b = float3(0.3541993807693, 0.4946349993233, 1);
    cube.tri[0].v.c = float3(-0.2596479168603, -0.5193091976541, 1);

    cube.tri[1].v.a = float3(-0.0404167391354, 0.6206929265151, 1);
    cube.tri[1].v.b = float3(0.6446806912547, 0.2370383654967, 1);
    cube.tri[1].v.c = float3(-0.4350328590401, 0.2425191449398, 1);
  */
  
  std::ofstream filea("data.txt", std::ios::out | std::ios::binary);
  if (filea.is_open()) {
    for (int asd = 0; asd < 0; asd++) {
      auto start = std::chrono::high_resolution_clock::now();
      gfx.render(&cube, &test_image);
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout << microseconds << "\n";
      filea << microseconds << '\n';
    }
    filea.close();
  } else
    std::cout << "Unable to open file";
  std::ofstream file("data.txt", std::ios::out | std::ios::binary);
  if (file.is_open()) {
    for (int asd = 0; asd < 1; asd++) {
      auto start = std::chrono::high_resolution_clock::now();
      gfx.render(&cube, &test_image);
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
      std::cout << microseconds << "\n";
      file << microseconds << '\n';
    }
    file.close();
  } else
    std::cout << "Unable to open file";
  out.output_image(&test_image, 0);

  return 0;
}
