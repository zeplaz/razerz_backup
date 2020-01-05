
#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
//#include <glm.hpp> // glm::mat4

#include <glm/glm.hpp> // glm::mat4
#include <glm/ext.hpp> // perspective, translate, rotate

#include <vector>
#include <string>
#include <fstream>

#include "mathII.hpp"


/*
* file contains the headers need for opengl and glfw
* as well as most of the defines, enums, and other fixed consts.
*/

static const int MAIN_SCREEN_WIDTH = 1000;
static const int MAIN_SCREEN_HIGHT = 800;

//macros
#define BUFFER_OFFSET(i) ((char *)NULL + (i))


/*
*definez
*/

#define L_AMBIENT 1
#define L_DIFFUSE 2
#define L_SPEKLER 3
#define L_DRECTION 4
#define L_POINT 5
#define L_SPOT 6

/*
* BITMASK ENUMZ template work
*/
//setup bitmaskable veratic Enums
//note check better veratdic template oprator sharing
template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}


template<typename Enum>
struct EnableBitMaskOperators
{
      static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs)
    );
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator |=(Enum &org,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return org =static_cast<Enum> (static_cast<underlying>(org) |  static_cast<underlying>(rhs));

};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (~static_cast<underlying>(rhs));
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (static_cast<underlying>(lhs)& static_cast<underlying>(rhs));
};

/*
*ENUMZ  USILTZEING BITMASKz functionality
*NOTE: require the template<> to activate bitmask
*/

enum class shader_type : unsigned char {
     SHADER_NULL         = 0x00,
     COMPUTE_SHADER      = 0x02,
     VERTEX_SHADER       = 0x04,
     FRAGMENT_SHADER     = 0x08,
     TESS_CONTROL_SHADER = 0x10,
     TESS_EVAL_SHADER    = 0x20,
     GEOMETRY_SHADER     = 0x40

};

template<>
struct EnableBitMaskOperators<shader_type>
{
    static const bool enable = true;
};

enum class M_Tex_Flag : unsigned char
{
  TEXTYR_NULL      = 0x00,
  TEXTYR_BASIC     = 0x02,
  TEXTYR_NORMAL    = 0x04,
  TEXTYR_SPEKTURAL = 0x08
};


template<>
struct EnableBitMaskOperators<M_Tex_Flag>
{
    static const bool enable = true;
};

enum class M_Model_Flag : unsigned char
{
  MODEL_NULL      = 0x00,
  MODEL_UNIFORM   = 0x02,
  MODEL_V_BUFF    = 0x04,
  MODEL_USE_INDIC = 0x20,
  MODEL_HAS_NORM  = 0x40

};
template<>
struct EnableBitMaskOperators<M_Model_Flag>
{
    static const bool enable = true;
};


template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}


/*
* class enum  and normal enumz listings.
*/

enum class Scene_Mesh_RDR{
  LIGHT_PROG01_SCENE01,
  BASIC_SHADER_SCENE01
};

enum class Scene_LIST
{
  SCENE_01
};


enum class Format {
    Format_Grayscale = 1, /**< one channel: grayscale */
    Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
    Format_RGB = 3, /**< three channels: red, green, blue */
    Format_RGBA = 4, /**< four channels: red, green, blue, alpha */
    Format_RGBA8 = 5,
    Format_RGB8 =6
};

enum WP_obj_tuple_feture
{
  INDEX_NUM,PAIR_NAME,VERTEX_VEC_DATA, FACE_VEC_DATA
};

enum SHDtype_index : uint8_t
{
  SHD_BASICA02_VERTEX =6,
  SHD_BASICA01_VERTEX =4,
  SHD_BASIC_FRAG = 5,
  SHD_LIGHTA1_VERTEX = 7,
  SHD_LIGHTA1_FRAG = 8
};

enum Lighting : bool
{
  HAS_LIGHTS = true,
  NO_LIGHT = false
};

enum PLY_obj_tuple_feturez
{
  VERTEXZ3D,NORMALZ3D,TEXTUCORD2D
};

enum  WarpMode : GLint{
  CLAMP_E = GL_CLAMP_TO_EDGE,
  MIRROR = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT,
  CLAMP_B = GL_CLAMP_TO_BORDER
};

enum class Filter{
  LINEAR,
  NEAREST,
  MIPMAP

};

enum Poly_face : GLint {
  FRONT = GL_FRONT,
  FANDB = GL_FRONT_AND_BACK,
  BACK =  GL_BACK

};

enum class P_Render_STYZ : GLint  {
      WIREFRAME =GL_LINE,
      FILL = GL_FILL ,
      POINT = GL_POINTS
};
typedef std::underlying_type<P_Render_STYZ>::type P_R_STYZ_utype;


enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


/*
*CONSTANTZ
*/

constexpr unsigned char ATTRBUT_DYNAMIC_DRAW{0b0000'0010};
constexpr unsigned char ATTRBUT_STATIC      {0b0000'0100};
constexpr unsigned char ATTRBUT_STREAM      {0b0000'1000};

constexpr unsigned char NULL_FLAG         {0b0000'0000};
constexpr unsigned char STATE_ACTIVE      {0b0000'0010};
constexpr unsigned char STATE_CULL        {0b0000'0100};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const float MAX_V_ANGLE = 88.0f;
