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

void inttohex(int a, char* charhex) {
  if ((a / 16) < 10) {
    charhex[0] = (a / 16) + '0';
  } else {
    charhex[0] = (a / 16) + 'A' - 10;
  }
  if ((a % 16) < 10) {
    charhex[1] = (a % 16) + '0';
  } else {
    charhex[1] = (a % 16) + 'A' - 10;
  }
  charhex[2] = 0;
}

int output::output_image(Image* image, int frame_num) {
  uint8_t* image_buffer;
  image_buffer = new uint8_t[(54 + (image->x * image->y * 4))];

  // BMP Header
  image_buffer[0x00] = 'B';
  image_buffer[0x01] = 'M';
  u32_to_array(image_buffer, 0x02, 54 + (image->x * image->y * 4));  //
  u16_to_array(image_buffer, 0x06, 0);
  u16_to_array(image_buffer, 0x08, 0);
  u32_to_array(image_buffer, 0x0A, 54);

  // DIB Header
  u32_to_array(image_buffer, 0x0E, 40);
  u32_to_array(image_buffer, 0x12, image->x);
  u32_to_array(image_buffer, 0x16, image->y);
  u16_to_array(image_buffer, 0x1A, 1);
  u16_to_array(image_buffer, 0x1C, 8 * 4);
  u32_to_array(image_buffer, 0x1E, 0);
  u32_to_array(image_buffer, 0x22, image->x * image->y * 4);
  u32_to_array(image_buffer, 0x26, 0);
  u32_to_array(image_buffer, 0x2A, 0);
  u32_to_array(image_buffer, 0x2E, 0);
  u32_to_array(image_buffer, 0x32, 0);
  int k;
  int index = 0;
  for (int i = 0; i < image->y; i++) {
    for (int j = 0; j < image->x; j++) {
      k = (i * image->x) + j;
      float3* pix = &image->pixels[(j*image->y)+i];
      image_buffer[0x36 + (k * 4) + 0] = (pix->x) * 255;
      image_buffer[0x36 + (k * 4) + 1] = (pix->y) * 255;
      image_buffer[0x36 + (k * 4) + 2] = (pix->z) * 255;
      image_buffer[0x36 + (k * 4) + 3] = 255;
      char hexint[3];
      inttohex((int)image_buffer[0x36 + (k * 4) + 0], hexint);
      //std::cout << "\n" << hexint;//(int)index++ << " " << hexint;  // << "\n" << (int)index++ << " " << (int)image_buffer[0x36 + (k * 4) + 1] << "\n" << (int)index++ << " " << (int)image_buffer[0x36 + (k * 4) + 2];
    }
  }
  //  for(;index<524287;index++){
  //    std::cout << "\n" << (int)index << " " << (int)0;
  //  }
  char imagename[30] = "build/images/test";
  int imagenameindex = 17;

  if (frame_num < 10) {
    imagename[imagenameindex + 0] = frame_num + '0';
    imagename[imagenameindex + 1] = '.';
    imagename[imagenameindex + 2] = 'b';
    imagename[imagenameindex + 3] = 'm';
    imagename[imagenameindex + 4] = 'p';
  } else if (frame_num < 100) {
    imagename[imagenameindex + 0] = (frame_num / 10) + '0';
    imagename[imagenameindex + 1] = (frame_num % 10) + '0';
    imagename[imagenameindex + 2] = '.';
    imagename[imagenameindex + 3] = 'b';
    imagename[imagenameindex + 4] = 'm';
    imagename[imagenameindex + 5] = 'p';
  } else if (frame_num < 1000) {
    imagename[imagenameindex + 0] = (frame_num / 100) + '0';
    imagename[imagenameindex + 1] = ((frame_num / 10) % 10) + '0';
    imagename[imagenameindex + 2] = (frame_num % 10) + '0';
    imagename[imagenameindex + 3] = '.';
    imagename[imagenameindex + 4] = 'b';
    imagename[imagenameindex + 5] = 'm';
    imagename[imagenameindex + 6] = 'p';
  }
  std::ofstream file(imagename, std::ios::out | std::ios::binary);
  if (file.is_open()) {
    file.write((char*)image_buffer, 54 + (image->x * image->y * 4));
    file.close();
  } else
    std::cout << "Unable to open file";
  return 0;
}

void output::rgbf_rgba(Image* image, unsigned char* imga) {
  int k;
  for (int i = 0; i < image->y; i++) {
    for (int j = 0; j < image->x; j++) {
      k = (i * image->x) + j;
      float3* pix = &image->pixels[(j*image->y)+i];
      imga[(k * 4) + 0] = (pix->x) * 255;
      imga[(k * 4) + 1] = (pix->y) * 255;
      imga[(k * 4) + 2] = (pix->z) * 255;
      imga[(k * 4) + 3] = 255;
    }
  }
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