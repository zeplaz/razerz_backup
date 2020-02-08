
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
typedef std::tuple<unsigned int,std::string,std::string,std::string,unsigned char>> texture_tupl;
typedef std::tuple<unsigned int,shader_type,std::string,std::string> shader_tuple_type;
typedef std::unordered_map<int,texture_tup> tt_map;

constexpr texture_tupl NULL_TT = std::make_tuple(0,"","","",0);
/*
DEFINEZ FOR PASEERXML->to uint
*/

//forall
constexpr unsigned int index = str2int("INDEX");
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



/*
XMLBASEPARSE FUNCTIONz
*/
  std::vector<std::string> run_xmlobj_parse(std::string& in_xml_path);


  unsigned int index_pars(std::string_view in_substring)
  {
    std::string parsindx;
    std::string index_num = in_substring.at(i+1);
    for(size_t k = 0; k< index_num.size(); k++)
    {
      if(index_num[k]=='[')
      {

        for(int ki = 0; ki <index_num.size()-1; ki++)
        {
          if(index_num[k+ki+1] ==']')
          break;

          parsindx += index_num[k+ki+1];
        }
      }
    }
     unsigned int out_index = stoul(parsindx);
     return out_index;
  }

#endif
