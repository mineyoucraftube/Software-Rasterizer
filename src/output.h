#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include "math.h"
#include "graphics.h"


class output {
 private:
  void u32_to_array(uint8_t* arrayy, size_t offset, uint32_t value);
  void u16_to_array(uint8_t* arrayy, size_t offset, uint16_t value);


 public:
  int output_image(Image* image, int frame_num);
};