#include <iostream>
#include "graphics.h"
#include "math.h"
#include "objparser.h"
#include "output.h"
#include "typedef.h"

#define SCREENSPACE_RANGE 3

output out;
output::image_s test_image;
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
  }
  /*

      trig[0].a = float2(-0.8899375528192, -0.1466161955218);
      trig[0].b = float2(0.3541993807693, 0.4946349993233);
      trig[0].c = float2(-0.2596479168603, -0.5193091976541);

      trig[1].a = float2(-0.0404167391354, 0.6206929265151);
      trig[1].b = float2(0.6446806912547, 0.2370383654967);
      trig[1].c = float2(-0.4350328590401, 0.2425191449398);
    */
  float2 screenposF;
  for (int i = 0; i < cube.num_triangle; i++) {
    if (cube.tri[i].n.z > 0) {
      float2 min = math::clamp(-SCREENSPACE_RANGE, math::min(math::min(cube.tri[i].v.a, cube.tri[i].v.b), cube.tri[i].v.c), SCREENSPACE_RANGE);
      float2 max = math::clamp(-SCREENSPACE_RANGE, math::max(math::max(cube.tri[i].v.a, cube.tri[i].v.b), cube.tri[i].v.c), SCREENSPACE_RANGE);

      int j_max = math::map(max.x, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, IMAGE_WIDTH) + 1;
      int k_max = math::map(max.y, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, IMAGE_HEIGHT) + 1;
      for (int j = math::map(min.x, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, IMAGE_WIDTH); j < j_max; j++) {
        for (int k = math::map(min.y, -SCREENSPACE_RANGE, SCREENSPACE_RANGE, 0, IMAGE_HEIGHT); k < k_max; k++) {
          screenposF = math::map(float2(j, k), 0, float2(IMAGE_WIDTH, IMAGE_HEIGHT), float2(-SCREENSPACE_RANGE, -SCREENSPACE_RANGE), float2(SCREENSPACE_RANGE, SCREENSPACE_RANGE));
          if (gfx.PointInTriangle(cube.tri[i].v, screenposF)) {
            test_image.pixels[j][k].r = cube.tri[i].color.x;  // * math::max(0, cube.tri[i].n.y);
            test_image.pixels[j][k].g = cube.tri[i].color.y;  // * math::max(0, cube.tri[i].n.y);
            test_image.pixels[j][k].b = cube.tri[i].color.z;  // * math::max(0, cube.tri[i].n.y);
          }
        }
      }
    }
  }
  out.output_image(&test_image, 0);

  return 0;
}