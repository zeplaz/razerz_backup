
//#include <iostream>

#ifndef PARSERLIB_HPP
#define PARSERLIB_HPP

#include <regex>

#include <fstream>
#include <sstream>
#include <iostream>

#include <utility>
#include <memory>
#include <algorithm>
#include <iterator>

#include <vector>
#include <array>
#include <tuple>
#include <string>

//string int handles
constexpr unsigned int str2int(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

 unsigned int str2int_run(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

//enumz
enum texture_touple_pos{
  TT_INDEX,
  TT_SUB_TYPE,
  TT_NAME,
  TT_FILEPATH,
  TT_FLAGZ
};

enum shader_touple_pos{
  ST_INDEX,
  ST_SHADER_TYPE,
  ST_NAME,
  ST_FILEPATH
};

//typedefz
typedef std::tuple<unsigned int,GLenum,std::string,std::string,unsigned char>> texture_tupl;
typedef std::tuple<unsigned int,shader_type,std::string,std::string> shader_tuple_type;
typedef std::unordered_map<unsigned int,texture_tup> tt_map;

constexpr texture_tupl NULL_TT = std::make_tuple(0,0,"","",0);
/*
DEFINEZ FOR PASEERXML->to uint
*/

//forall
constexpr unsigned int index = str2int("INDEX");
constexpr unsigned int flagz = str2int("FLAGZ");
//forobjz
constexpr unsigned int item_type = str2int("ITEM_TYPE");
constexpr unsigned int subtype = str2int("SUB_TYPE")

//for shaderz
constexpr unsigned int h_shad_type = str2int("SHADER_TYPE");
constexpr unsigned int h_file_root = str2int("file_root");
constexpr unsigned int h_shad_name = str2int("NAME");
constexpr unsigned int h_shad_title = str2int("shader_glsl");

//for texture

constexpr unsigned int t_name = str2int("NAME");
constexpr unsigned int t_file_root = str2int("file_root");

//TEXTURETYPEZ

/*
xml litreals conversionchart texture Types
texture1d->GL_TEXTURE_1D
texture2d -> GL_TEXTURE_2D
texture3d -> GL_TEXTURE_3D
texturerec ->GL_TEXTURE_RECTANGLE
texturebuff ->GL_TEXTURE_BUFFER
texturecubmap ->GL_TEXTURE_CUBE_MAP
texture1d_array ->GL_TEXTURE_1D_ARRAY
texture2d_array ->GL_TEXTURE_2D_ARRAY
texturecubmap_array->GL_TEXTURE_CUBE_MAP_ARRAY
texture2d_multi->GL_TEXTURE_2D_MULTISAMPLE
texture2d_multi_array->GL_TEXTURE_2D_MULTISAMPLE_ARRAY
*/

/*
XMLBASEPARSE FUNCTIONz
*/
  std::vector<std::string> run_xmlobj_parse(std::string& in_xml_path);
  unsigned int index_pars(std::string_view in_substring);

#endif
