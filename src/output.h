#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>

#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024

class output {
 private:
  void u32_to_array(uint8_t* arrayy, size_t offset, uint32_t value);
  void u16_to_array(uint8_t* arrayy, size_t offset, uint16_t value);

  struct pixel_s {
    float r;
    float g;
    float b;
  };

 public:
  struct image_s {
    pixel_s pixels[IMAGE_WIDTH][IMAGE_HEIGHT];
  };
  int output_image(image_s* image, int frame_num);
};