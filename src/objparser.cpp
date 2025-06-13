#include "objparser.h"

float exponent(float a, int b) {
  float c = 1;
  for (; b > 0; b--) {
    c *= a;
  }
  for (; b < 0; b++) {
    c /= a;
  }
  return c;
}

raw_object get_obj_params(char* file, size_t size) {
  size_t index = 0;
  size_t v = 0, n = 0, t = 0, f = 0;
  while (index < size) {
    switch (file[index]) {
      case 'v':
        if ((index + 1) < size) {
          switch (file[index + 1]) {
            case 'n':
              n++;
              break;

            case 't':
              t++;
              break;

            case ' ':
              v++;
              break;
          }
        }
        break;

      case 'f':
        f++;
        break;

      default:
        break;
    }
    while ((file[index] != '\n') && (index < size)) {
      index++;
    }
    if (index < size) {
      index++;
    }
  }
  return raw_object(v, n, t, f);
}

float parsefloat(char* file, indexing index) {
  float num = 0;
  float dec = 0;
  int deci = 1;
  bool is_neg = 0;
  bool is_dec = 0;
  bool padding = 1;
  while (index.file_index < index.file_size) {
    if (('0' <= file[index.file_index]) && (file[index.file_index] <= '9')) {
      padding = 0;
      if (!is_dec) {
        num *= 10;
        num += file[index.file_index] - 48;
      } else {
        dec += (file[index.file_index] - 48) / exponent(10, deci);
        deci++;
      }
    } else if (file[index.file_index] == '-') {
      padding = 0;
      is_neg = 1;
    } else if (file[index.file_index] == '.') {
      padding = 0;
      is_dec = 1;
    } else {
      if (!padding)
        return num + dec;
    }
    if ((index.file_index + 1) < index.file_size)
      index.file_index++;
  }
}

int parseint(char* file, indexing index) {
  int num = 0;
  bool is_neg = 0;
  bool padding = 1;
  while (index.file_index < index.file_size) {
    if (('0' <= file[index.file_index]) && (file[index.file_index] <= '9')) {
      padding = 0;
      num *= 10;
      num += file[index.file_index] - 48;
    } else if (file[index.file_index] == '-') {
      padding = 0;
      is_neg = 1;
    } else {
      if (!padding)
        return num;
    }
    if ((index.file_index + 1) < index.file_size)
      index.file_index++;
  }
}

void parsevert(char* file, raw_object object, indexing index) {
  object.verts[index.v].x = parsefloat(file, index);
  object.verts[index.v].y = parsefloat(file, index);
  object.verts[index.v].z = parsefloat(file, index);
  if ((index.v + 1) < object.num_vertice)
    index.v++;
}
void parsenormal(char* file, raw_object object, indexing index) {
  object.normals[index.n].x = parsefloat(file, index);
  object.normals[index.n].y = parsefloat(file, index);
  object.normals[index.n].z = parsefloat(file, index);
  if ((index.n + 1) < object.num_normal)
    index.n++;
}
void parseUV(char* file, raw_object object, indexing index) {
  object.uvs[index.t].x = parsefloat(file, index);
  object.uvs[index.t].y = parsefloat(file, index);
  if ((index.t + 1) < object.num_uv)
    index.t++;
}
void parseface(char* file, raw_object object, indexing index) {
  object.faces[index.f].verti = parseint(file, index);
  object.faces[index.f].uvi = parseint(file, index);
  object.faces[index.f].normali = parseint(file, index);
  if ((index.f + 1) < object.num_face)
    index.f++;
}

void parseline(char* file, raw_object object, indexing index) {
  switch (file[index.file_index]) {
    case 'v':
      if ((index.file_index + 1) < index.file_size)
        index.file_index++;

      switch (file[index.file_index]) {
        case ' ':
          parsevert(file, object, index);
          break;
        case 'n':
          // if ((index.file_index + 1) < index.file_size)
          // index.file_index++;
          parsenormal(file, object, index);
          break;

        case 't':
          // if ((index.file_index + 1) < index.file_size)
          // index.file_index++;
          parseUV(file, object, index);
          break;
      }

      break;

    case 'f':
      // if ((index.file_index + 1) < index.file_size)
      // index.file_index++;
      parseface(file, object, index);
      break;

    default:
      break;
  }
}

raw_object objparser::parse(const char* filename) {
  std::ifstream objfile(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!objfile.is_open()) {
    std::cout << "Unable to open file";
    return;
  }
  indexing index(objfile.tellg());
  char* file = new char[index.file_size];

  objfile.seekg(0, std::ios::beg);
  objfile.read(file, index.file_size);
  objfile.close();

  raw_object object = get_obj_params(file, index.file_size);
  for (; index.file_index < index.file_size;) {
    parseline(file, object, index);
    while ((file[index.file_index] != '\n') && (index.file_index < index.file_size))
      index.file_index++;

    if ((index.file_index + 1) < index.file_size)
      index.file_index++;
  }

  // parsefloat(file, 0);
  std::cout << file[2] << '\n';

  delete[] file;
  return object;
}