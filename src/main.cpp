#include <chrono>
#include <iostream>
#include "graphics.h"
#include "math.h"
#include "number.h"
#include "objparser.h"
#include "output.h"
#include "typedef.h"

output out;
graphics gfx;
objparser obp;



std::chrono::_V2::system_clock::time_point start;
void start_timer() {
  start = std::chrono::high_resolution_clock::now();
}
void print_timer() {
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << "\n";
}
void print_obj_model_info(obj_object model) {
  std::cout << "num_vertice: " << model.num_vertice << '\n';
  std::cout << "num_normal: " << model.num_normal << '\n';
  std::cout << "num_uv: " << model.num_uv << '\n';
  std::cout << "num_face: " << model.num_face << '\n';
  for (int i = 0; i < model.num_vertice; i++) {
    std::cout << "v[" << i << "]: " << model.verts[i].x << " " << model.verts[i].y << " " << model.verts[i].z << '\n';
  }
  for (int i = 0; i < model.num_normal; i++) {
    std::cout << "n[" << i << "]: " << model.normals[i].x << " " << model.normals[i].y << " " << model.normals[i].z << '\n';
  }
  for (int i = 0; i < model.num_uv; i++) {
    std::cout << "t[" << i << "]: " << model.uvs[i].x << " " << model.uvs[i].y << '\n';
  }
  for (int i = 0; i < model.num_face; i++) {
    std::cout << "f[" << i << "]:";
    for (int j = 0; j < model.faces[i]->num_vert; j++) {
      std::cout << " " << model.faces[i]->verti[j] << "/" << model.faces[i]->uvi[j] << "/" << model.faces[i]->normali[j];
    }
    std::cout << '\n';
  }
}
void output_obj_model(obj_object model) {
  std::ofstream file("benchy.obj", std::ios::out | std::ios::binary);
  if (file.is_open()) {
    file << "o Benchy\n";
    for (int i = 0; i < model.num_vertice; i++) {
      // model.verts[i] = number::randcoloring[i];
      file << "v " << model.verts[i].x << " " << model.verts[i].y << " " << model.verts[i].z << '\n';
    }
    for (int i = 0; i < model.num_normal; i++) {
      file << "vn " << model.normals[i].x << " " << model.normals[i].y << " " << model.normals[i].z << '\n';
    }
    for (int i = 0; i < model.num_uv; i++) {
      file << "vt " << model.uvs[i].x << " " << model.uvs[i].y << '\n';
    }
    file << "s 0\n";
    for (int i = 0; i < model.num_face; i++) {
      file << "f";
      for (int j = 0; j < model.faces[i]->num_vert; j++) {
        file << " " << model.faces[i]->verti[j] << "/" << model.faces[i]->uvi[j] << "/" << model.faces[i]->normali[j];
      }
      file << '\n';
    }
    file << '\n';

  } else
    std::cout << "Unable to open file";
  file.close();
}
void print_simple_model_info(simple_object model) {
  std::cout << model.num_triangle << "\n";
  for (int i = 0; i < model.num_triangle; i++) {
    std::cout << "t[" << i << "] ";
    std::cout << model.tri[i].v.a.x << "  \t ";
    std::cout << model.tri[i].v.a.y << "  \t ";
    std::cout << model.tri[i].v.a.z << "  \t \t ";
    std::cout << model.tri[i].v.b.x << "  \t ";
    std::cout << model.tri[i].v.b.y << "  \t ";
    std::cout << model.tri[i].v.b.z << "  \t \t ";
    std::cout << model.tri[i].v.c.x << "  \t ";
    std::cout << model.tri[i].v.c.y << "  \t ";
    std::cout << model.tri[i].v.c.z << "\n";
  }
    /*
    cube.tri[0].v.a = float3(-0.8899375528192, -0.1466161955218, 1);
    cube.tri[0].v.b = float3(0.3541993807693, 0.4946349993233, 1);
    cube.tri[0].v.c = float3(-0.2596479168603, -0.5193091976541, 1);

    cube.tri[1].v.a = float3(-0.0404167391354, 0.6206929265151, 1);
    cube.tri[1].v.b = float3(0.6446806912547, 0.2370383654967, 1);
    cube.tri[1].v.c = float3(-0.4350328590401, 0.2425191449398, 1);
  */

}

Image test_image;
int main() {

  obj_object testing = obp.parse("models/suzanne3.obj");
  simple_object cube = obp.rawObjToSimpleObj(testing);
  simple_object triangles(50);
  for (int i = 0; i < triangles.num_triangle; i++) {
    triangles.tri[i].n = float3(0, 0, 1);
    triangles.tri[i].v.a = number::randcoloring[i * 3 + 0] * 2 - 1;
    triangles.tri[i].v.b = number::randcoloring[i * 3 + 1] * 2 - 1;
    triangles.tri[i].v.c = number::randcoloring[i * 3 + 2] * 2 - 1;
  }
  simple_object speeds(50);
  for (int i = 0; i < speeds.num_triangle; i++) {
    speeds.tri[i].v.a = (number::randcoloring[i * 3 + 0 + 100] * 2 - 1) / 10;
    speeds.tri[i].v.b = (number::randcoloring[i * 3 + 1 + 100] * 2 - 1) / 10;
    speeds.tri[i].v.c = (number::randcoloring[i * 3 + 2 + 100] * 2 - 1) / 10;
  }
  // output_obj_model(testing);
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < triangles.num_triangle; j++) {
      triangles.tri[j].v.a = triangles.tri[j].v.a + speeds.tri[j].v.a;
      triangles.tri[j].v.b = triangles.tri[j].v.b + speeds.tri[j].v.b;
      triangles.tri[j].v.c = triangles.tri[j].v.c + speeds.tri[j].v.c;
      if (triangles.tri[j].v.a.x < -1 || triangles.tri[j].v.a.x > 1)
        speeds.tri[j].v.a.x = -speeds.tri[j].v.a.x;
      if (triangles.tri[j].v.a.y < -1 || triangles.tri[j].v.a.y > 1)
        speeds.tri[j].v.a.y = -speeds.tri[j].v.a.y;
      if (triangles.tri[j].v.a.z < -1 || triangles.tri[j].v.a.z > 1)
        speeds.tri[j].v.a.z = -speeds.tri[j].v.a.z;
      if (triangles.tri[j].v.b.x < -1 || triangles.tri[j].v.b.x > 1)
        speeds.tri[j].v.b.x = -speeds.tri[j].v.b.x;
      if (triangles.tri[j].v.b.y < -1 || triangles.tri[j].v.b.y > 1)
        speeds.tri[j].v.b.y = -speeds.tri[j].v.b.y;
      if (triangles.tri[j].v.b.z < -1 || triangles.tri[j].v.b.z > 1)
        speeds.tri[j].v.b.z = -speeds.tri[j].v.b.z;
      if (triangles.tri[j].v.c.x < -1 || triangles.tri[j].v.c.x > 1)
        speeds.tri[j].v.c.x = -speeds.tri[j].v.c.x;
      if (triangles.tri[j].v.c.y < -1 || triangles.tri[j].v.c.y > 1)
        speeds.tri[j].v.c.y = -speeds.tri[j].v.c.y;
      if (triangles.tri[j].v.c.z < -1 || triangles.tri[j].v.c.z > 1)
        speeds.tri[j].v.c.z = -speeds.tri[j].v.c.z;
    }
    for (int i = 0; i < test_image.x; i++) {
      for (int j = 0; j < test_image.y; j++) {
        test_image.pixels[i][j] = 0;
      }
    }
    start_timer();
    gfx.render(&cube, &test_image);
    print_timer();
    out.output_image(&test_image, i);
  }
  return 0;
}
