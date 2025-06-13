#include <iostream>
#include "graphics.h"
#include "output.h"
#include "typedef.h"
#include "objparser.h"

output out;
output::image_s test_image;
graphics gfx;
float2 test;
float2 testing;
float2 floating;
triangle2 trig[2];

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float2 map2(float2 x, float2 in_min, float2 in_max, float2 out_min, float2 out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


objparser obp;

int main() {
  raw_object testing = obp.parse("cubexyz.obj");

  std::cout << testing.num_face << '\n';

/*  trig[0].a = float2(-0.8899375528192,-0.1466161955218);
  trig[0].b = float2(0.3541993807693, 0.4946349993233);
  trig[0].c = float2(-0.2596479168603, -0.5193091976541);

  trig[1].a = float2(-0.0404167391354, 0.6206929265151);
  trig[1].b = float2(0.6446806912547, 0.2370383654967);
  trig[1].c = float2(-0.4350328590401, 0.2425191449398);

  int k = ' ';
  float2 screenposF;
  for (int i = 0; i < IMAGE_HEIGHT; i++) {
    for (int j = 0; j < IMAGE_WIDTH; j++) {
      screenposF = map2(float2(j, i), float2(0, 0), float2(IMAGE_WIDTH, IMAGE_HEIGHT), float2(-1, -1), float2(1, 1));
      test_image.pixels[i][j].b = gfx.PointInTriangle(trig[0], screenposF);
      test_image.pixels[i][j].r = gfx.PointInTriangle(trig[1], screenposF);
      // k = (i * IMAGE_WIDTH) + j;
      // test_image.pixels[i][j].r = i % 256;
      // test_image.pixels[i][j].g = j % 256;
      // test_image.pixels[i][j].b = k / ((IMAGE_HEIGHT * IMAGE_WIDTH) / 256);
    }
  }
  out.output_image(&test_image, 0);
*/
  return 0;
}