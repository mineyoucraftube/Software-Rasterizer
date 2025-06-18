#include "output.h"

void output::u32_to_array(uint8_t* arrayy, size_t offset, uint32_t value) {
  arrayy[offset + 0] = value & 0xFF;
  arrayy[offset + 1] = (value >> 8) & 0xFF;
  arrayy[offset + 2] = (value >> 16) & 0xFF;
  arrayy[offset + 3] = (value >> 24) & 0xFF;
}
void output::u16_to_array(uint8_t* arrayy, size_t offset, uint16_t value) {
  arrayy[offset + 0] = value & 0xFF;
  arrayy[offset + 1] = (value >> 8) & 0xFF;
}

int output::output_image(image_s* image, int frame_num) {
  uint8_t* image_buffer;
  image_buffer = new uint8_t[(54 + (IMAGE_WIDTH * IMAGE_HEIGHT * 4))];

  // BMP Header
  image_buffer[0x00] = 'B';
  image_buffer[0x01] = 'M';
  u32_to_array(image_buffer, 0x02, 54 + (IMAGE_WIDTH * IMAGE_HEIGHT * 4));  //
  u16_to_array(image_buffer, 0x06, 0);
  u16_to_array(image_buffer, 0x08, 0);
  u32_to_array(image_buffer, 0x0A, 54);

  // DIB Header
  u32_to_array(image_buffer, 0x0E, 40);
  u32_to_array(image_buffer, 0x12, IMAGE_WIDTH);
  u32_to_array(image_buffer, 0x16, IMAGE_HEIGHT);
  u16_to_array(image_buffer, 0x1A, 1);
  u16_to_array(image_buffer, 0x1C, 8 * 4);
  u32_to_array(image_buffer, 0x1E, 0);
  u32_to_array(image_buffer, 0x22, IMAGE_WIDTH * IMAGE_HEIGHT * 4);
  u32_to_array(image_buffer, 0x26, 0);
  u32_to_array(image_buffer, 0x2A, 0);
  u32_to_array(image_buffer, 0x2E, 0);
  u32_to_array(image_buffer, 0x32, 0);
  int k;
  for (int i = 0; i < IMAGE_HEIGHT; i++) {
    for (int j = 0; j < IMAGE_WIDTH; j++) {
      k = (i * IMAGE_WIDTH) + j;
      pixel_s* pix = &image->pixels[j][i];
      image_buffer[0x36 + (k * 4) + 0] = (pix->b) * 255;
      image_buffer[0x36 + (k * 4) + 1] = (pix->g) * 255;
      image_buffer[0x36 + (k * 4) + 2] = (pix->r) * 255;
      image_buffer[0x36 + (k * 4) + 3] = 0;
    }
  }

  std::ofstream file("test.bmp", std::ios::out | std::ios::binary);
  if (file.is_open()) {
    file.write((char*)image_buffer, 54 + (IMAGE_WIDTH * IMAGE_HEIGHT * 4));
    file.close();
  } else
    std::cout << "Unable to open file";
  return 0;
}

// reading an entire binary file
// using namespace std;
/*
int main() {
  std::streampos size;
  char* memblock;

  std::fstream file("example.bin", std::ios::in | std::ios::binary | std::ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    memblock = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(memblock, size);
    file.close();

    std::cout << "the entire file content is in memory";

    delete[] memblock;
  } else
    std::cout << "Unable to open file";
  return 0;
}
  */