#include "objparser.h"
#include "number.h"

obj_object objparser::get_obj_params(char* file, size_t size) {
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
      case 'r':
        rewind_verts = 1;
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
  return obj_object(v, n, t, f);
}

float objparser::parsefloat(char* file, indexing* index) {
  float num = 0;
  float dec = 0;
  int deci = 1;
  bool is_neg = 0;
  bool is_dec = 0;
  bool padding = 1;
  while (index->file_index < index->file_size) {
    if (('0' <= file[index->file_index]) && (file[index->file_index] <= '9')) {
      padding = 0;
      if (!is_dec) {
        num *= 10;
        num += file[index->file_index] - 48;
      } else {
        dec += (file[index->file_index] - 48) / math::exponent(10, deci);
        deci++;
      }
    } else if (file[index->file_index] == '-') {
      padding = 0;
      is_neg = 1;
    } else if (file[index->file_index] == '.') {
      padding = 0;
      is_dec = 1;
    } else {
      if (!padding)
        if (!is_neg) {
          return num + dec;
        } else {
          return -(num + dec);
        }
    }
    if ((index->file_index + 1) < index->file_size) {
      // std::cout << file[index->file_index];

      index->file_index++;
    }
  }
  return 0;
}
int objparser::parseint(char* file, indexing* index) {
  int num = 0;
  bool is_neg = 0;
  bool padding = 1;
  while (index->file_index < index->file_size) {
    if (('0' <= file[index->file_index]) && (file[index->file_index] <= '9')) {
      padding = 0;
      num *= 10;
      num += file[index->file_index] - 48;
    } else if (file[index->file_index] == '-') {
      padding = 0;
      is_neg = 1;
    } else {
      if (!padding)
        if (!is_neg) {
          return num;
        } else {
          return -num;
        }
    }
    if ((index->file_index + 1) < index->file_size) {
      // std::cout << file[index->file_index];
      index->file_index++;
    }
  }
  return 0;
}

void objparser::parsevert(char* file, obj_object object, indexing* index) {
  object.verts[index->v].x = parsefloat(file, index);
  object.verts[index->v].y = parsefloat(file, index);
  object.verts[index->v].z = parsefloat(file, index);
  if ((index->v + 1) < object.num_vertice)
    index->v++;
}
void objparser::parsenormal(char* file, obj_object object, indexing* index) {
  object.normals[index->n].x = parsefloat(file, index);
  object.normals[index->n].y = parsefloat(file, index);
  object.normals[index->n].z = parsefloat(file, index);
  if ((index->n + 1) < object.num_normal)
    index->n++;
}
void objparser::parseUV(char* file, obj_object object, indexing* index) {
  object.uvs[index->t].x = parsefloat(file, index);
  object.uvs[index->t].y = parsefloat(file, index);
  if ((index->t + 1) < object.num_uv)
    index->t++;
}
bool isnewline(char* file, indexing* index) {
  return (file[index->file_index] == '\n') || (file[index->file_index] == '\r');
}
void objparser::parseface(char* file, obj_object object, indexing* index) {
  const size_t backup_index = index->file_index;
  int vertnumber = 0;
  while (!isnewline(file, index) && (index->file_index < index->file_size)) {
    // std::cout << file[index->file_index];
    parseint(file, index);
    parseint(file, index);
    parseint(file, index);
    vertnumber++;
  }

  index->file_index = backup_index;
  if (vertnumber >= 3) {
    object.faces[index->f] = new face(vertnumber);
    if (!rewind_verts) {
      for (int i = 0; i < object.faces[index->f]->num_vert; i++) {
        object.faces[index->f]->verti[i] = parseint(file, index) - 1;
        object.faces[index->f]->uvi[i] = parseint(file, index) - 1;
        object.faces[index->f]->normali[i] = parseint(file, index) - 1;
      }
    } else {
      for (int i = object.faces[index->f]->num_vert-1; i >= 0; i--) {
        object.faces[index->f]->verti[i] = parseint(file, index) - 1;
        object.faces[index->f]->uvi[i] = parseint(file, index) - 1;
        object.faces[index->f]->normali[i] = parseint(file, index) - 1;
      }
    }
    if ((index->f + 1) < object.num_face)
      index->f++;
  }
}

void objparser::parseline(char* file, obj_object object, indexing* index) {
  switch (file[index->file_index]) {
    case 'v':
      if ((index->file_index + 1) < index->file_size) {
        // std::cout << file[index->file_index];
        index->file_index++;
      }

      switch (file[index->file_index]) {
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
// when exporting in blender, set forward axis -z and up axis y for veiw point [numpad 1] = rendered here
// forward axis = top of view
// top axis = towards camera
obj_object objparser::parse(const char* filename) {
  std::ifstream objfile(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!objfile.is_open()) {
    std::cout << "Unable to open file";
    return obj_object(0, 0, 0, 0);
  }
  indexing index(objfile.tellg());
  char* file = new char[index.file_size];

  objfile.seekg(0, std::ios::beg);
  objfile.read(file, index.file_size);
  objfile.close();

  obj_object object = get_obj_params(file, index.file_size);
  for (; index.file_index < index.file_size;) {
    // std::cout << "parse:\n";
    parseline(file, object, &index);
    // std::cout << "\nskip:\n";
    while ((file[index.file_index] != '\n') && (index.file_index < index.file_size)) {
      // std::cout << file[index.file_index];
      index.file_index++;
    }
    // std::cout << "\n";

    if ((index.file_index) < index.file_size) {
      // std::cout << file[index.file_index];
      index.file_index++;
    }
  }

  // parsefloat(file, 0);
  // std::cout << file[2] << '\n';

  delete[] file;
  return object;
}

simple_object objparser::rawObjToSimpleObj(obj_object rawobj) {
  int trianglenumber = 0;
  for (int i = 0; i < rawobj.num_face; i++) {
    if (rawobj.faces[i]->num_vert == 3) {
      trianglenumber += rawobj.faces[i]->num_vert - 2;
    } else {
      if (rawobj.faces[i]->num_vert < 3) {
        std::cout << "why is your face less than 3 verticies?";
      }
      if (rawobj.faces[i]->num_vert > 3) {
        // yo_triangle_aint_a_triangle_also_how_tf_did_you_get_here:
        std::cout << "triangulate your faces, i don't support more than 3 verticies per face yet";
      }
      return simple_object(0);
    }
  }

  simple_object simobj(trianglenumber);
  size_t triangleindex = 0;
  for (int i = 0; (i < rawobj.num_face) && (i < trianglenumber); i++) {
    if (rawobj.faces[i]->num_vert == 3) {
      /*      if (i == 1) {
              std::cout << rawobj.faces[i]->verti[0] << ' ';
              std::cout << rawobj.faces[i]->verti[1] << ' ';
              std::cout << rawobj.faces[i]->verti[2] << '\n';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[0]].x << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[0]].y << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[0]].z << '\t';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[1]].x << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[1]].y << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[1]].z << '\t';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[2]].x << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[2]].y << ' ';
              std::cout << rawobj.verts[rawobj.faces[i]->verti[2]].z << '\n';
            }*/
      simobj.tri[i].v.a = rawobj.verts[rawobj.faces[i]->verti[0]];
      simobj.tri[i].v.b = rawobj.verts[rawobj.faces[i]->verti[1]];
      simobj.tri[i].v.c = rawobj.verts[rawobj.faces[i]->verti[2]];
      simobj.tri[i].n = (rawobj.normals[rawobj.faces[i]->normali[0]] + rawobj.normals[rawobj.faces[i]->normali[1]] + rawobj.normals[rawobj.faces[i]->normali[2]]) / float3(3, 3, 3);
      simobj.tri[i].uv.a = rawobj.uvs[rawobj.faces[i]->uvi[0]];
      simobj.tri[i].uv.b = rawobj.uvs[rawobj.faces[i]->uvi[1]];
      simobj.tri[i].uv.c = rawobj.uvs[rawobj.faces[i]->uvi[2]];
      simobj.tri[i].color = number::randcoloring[i];

    } else {
      std::cout << "how did you get here? i ALREADY checked that your faces were all 3 verticies";  // no, seriously, how?
      return simple_object(0);
    }
  }
  return simobj;
}
/*
struct simple_object {
  const size_t num_triangle;
  triangle* tri;
};
struct triangle {
  float3 a;
  float3 b;
  float3 c;
  float3 na;
  float3 nb;
  float3 nc;
  float2 uva;
  float2 uvb;
  float2 uvc;
  float3 color;
};
*/
/*
struct obj_object {
  const size_t num_vertice;
  const size_t num_normal;
  const size_t num_uv;
  const size_t num_face;
  float3* verts;
  float3* normals;
  float2* uvs;
  face** faces;
};
struct face {
  const int num_vert;
  int* verti;
  int* uvi;
  int* normali;
};
*/