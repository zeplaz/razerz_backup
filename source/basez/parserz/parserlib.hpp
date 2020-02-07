
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

//typedefz
typedef std::tuple<std::string,std::pair<int,int>> texture_tup;
typedef std::tuple<unsigned int,
           shader_type,std::string,std::string> shader_tuple_type;


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
;
constexpr unsigned int t_file_root = str2int("file_root");



/*
XMLBASEPARSE FUNCTIONz
*/
  std::vector<std::string> run_xmlobj_parse(std::string& in_xml_path);

#endif
