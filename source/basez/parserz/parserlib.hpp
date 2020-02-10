
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
#include <unordered_map>

//string int handles
constexpr unsigned int str2int(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

 unsigned int str2int_run(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

//enumz for parserindexpos

enum Texture_Touple_pos{
  //TT_INDEX,      //uint
  TEXIMG_PARAMZ, //teximage2d_parmz
  TT_NAME,       //string
  TT_FILEPATH,   //string
  TT_FLAGZ       //0b00000etyc??
};

enum Teximg2d_Paramz_pos
{
TI2D_TARGET,       //GLenum
TI2D_COLOUR_COMP, //GLint
TI2D_PIX_FORMATE, //GLenum
TI2D_PIX_DATATYPE //GLenum
};

enum Shader_Touple_pos{
  ST_INDEX,
  ST_SHADER_TYPE,
  ST_NAME,
  ST_FILEPATH
};

//typedefz

//target,internalformate,pixel data format,textture_type
typedef std::tuple<GLenum,Glint,GLenum,GLenum> teximage2d_parmz;
//,teximage2d_parmz,name,filepath,flagz
typedef std::tuple<teximage2d_parmz,std::string,std::string,unsigned char>> texture_tupl;
//index,shader_type,name,filepath
typedef std::tuple<unsigned int,shader_type,std::string,std::string> shader_tupl;

//MAPS typedefed
typedef std::unordered_map<unsigned int,texture_tup> tt_map;

//NULLtouples
constexpr inteximage2d NULL_TI2D = std::make_tuple(0,0,0,0);
constexpr texture_tupl NULL_TT   = std::make_tuple(0,NULL_TI2D,"","",0);

/*
DEFINEZ FOR Resource Types ->
to uint for parsing switch
*/

//forall
constexpr unsigned int index = str2int("INDEX");
constexpr unsigned int name  = str2int("NAME");
constexpr unsigned int file_root = str2int("file_root");
constexpr unsigned int flagz = str2int("FLAGZ");

//forobjz
constexpr unsigned int item_type = str2int("ITEM_TYPE");
constexpr unsigned int subtype   = str2int("SUB_TYPE")

//for shaderz
constexpr unsigned int h_shad_type  = str2int("SHADER_TYPE");
constexpr unsigned int h_shad_title = str2int("shader_glsl");

//for texture
constexpr unsigned int t_colour_comp   = str2int("gl_colour_components");
constexpr unsigned int t_pix_formate   = str2int("gl_formate_pix");
constexpr unsigned int t_pixdata_type  = str2int("gl_pixdata_type");

/*
XMLBASEPARSE FUNCTIONz
*/
  std::vector<std::string> run_xmlobj_parse(std::string& in_xml_path);
  unsigned int index_pars(std::string_view in_substring);

  class xml_parser{

    public :
    int load_run(std::string in_pathxml);
    virtual int item_selection(std::string& in_obj_type,std::vector<std::string>& in_substingz) = 0;

    };

#endif
