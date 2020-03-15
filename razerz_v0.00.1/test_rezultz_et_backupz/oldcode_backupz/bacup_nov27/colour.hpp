
//makcros from game gemz.
#pragma once

#include "mathII.hpp"
#include <vector>
#include <valarray>
// defines for small numbers
#define EPSILON_E3 (float)(1E-3)
#define EPSILON_E4 (float)(1E-4)
#define EPSILON_E5 (float)(1E-5)
#define EPSILON_E6 (float)(1E-6)
// this builds a 24 bit color value in 8.8.8 format
#define _RGB24BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) )
// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

// bit manipulation macros
#define SET_BIT(word,bit_flag)   ((word)=((word) | (bit_flag)))
#define RESET_BIT(word,bit_flag) ((word)=((word) & (~bit_flag)))

#define DD_PIXEL_FORMAT888      24
#define DD_PIXEL_FORMATALPHA888 32

#define VERTEX4DTV1_ATTR_NULL             0x0000 // this vertex is empty
#define VERTEX4DTV1_ATTR_POINT            0x0001
#define VERTEX4DTV1_ATTR_NORMAL           0x0002
#define ATTR_TEXTURE          0x0004

const size_t FOUR = 4;

typedef struct Point3D_32_Type
{
  mathz::vector3_vala<float> coordz;
  unsigned short int colour_32;

  Point3D_32_Type() = default;
  Point3D_32_Type(float x, float y, float z,int alpha,int red, int green, int blue)
  {
    coordz[0] =x;
    coordz[1] =y;
    coordz[2] =z;
    colour_32 = _RGB32BIT(alpha,red,green,blue);
  }
  void set_cordz(float x, float y, float z)
  {
    coordz[0] =x;
    coordz[1] =y;
    coordz[2] =z;
  }
  void set_colour(int alpha,int red, int green, int blue)
  {
    colour_32 = _RGB32BIT(alpha,red,green,blue);
  }
} Point3D_32, *Point3D_32_ptr;


typedef struct param_linez3D_type
{
  mathz::vector3_vala<float> drec_vec;

  Point3D_32 p0;
  Point3D_32 p1;
} param_linez3D,*param_linez3D_ptr;


typedef struct Point4D_type
{
 union
 {
  std::valarray<float> coordinatez;

  struct {
    float x;
    float y;
    float z;
    float w;
  };

  };
} Point4D,*Point4D_ptr;


typedef struct line_3dmono_type
{
  unsigned short int colour_32;
  int end_p1, end_p2;
} line3dmono_32, *line3dmono_32_prt;

typedef struct line_3d2c_type
{
  unsigned short int colour_32A,colour_32B;
  int end_p1, end_p2;
} line_3d2c, *line_3d2c_prt;

typedef struct triangle_tri32_type
{
  Point3D_32 p1,p2,p3;
} triangle_tri32, *triangle_tri32_ptr;

typedef struct triangle_full_type
{
  std::vector<Point3D_32> pixel_vec;
  mathz::vector3_vala<float> p1,p2,p3;

} triangle_full, *triangle_full_prt;

typedef struct BitMap_type
{
  int state;
  int attrabutes;
  float x,y;
  int width,hight;
  int number_bytes;
  unsigned char *buffer_pixelz;
} BitMap,*BitMap_ptr;

typedef struct Vertex3D_32type
{
  mathz::vector3_vala<float> normalz;
  Point3D_32 point;
  float texture_cords[2];

  float intensity;
  int attrabutez;

} Vertex3D_32, Vertex3D_32_ptr;

typedef struct PolyF3D_type
{
  int state;
  int attrabutes;
  int colour;
  int lit_colour[3];

  mathz::vector3_vala<float> normalz;
  BitMap_ptr texture_prt;
  int material_index;

  float poly_length;
  float avg_z;

  Vertex3D_32 vertex_list[3];
  Vertex3D_32 tranz_vertex_list[3];
}PolyF3D, *PolyF3D_ptr;

//move to gllib
