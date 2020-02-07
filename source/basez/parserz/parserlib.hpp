
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

//for shaderz
constexpr unsigned int h_index = str2int("INDEX");
constexpr unsigned int h_shad_type = str2int("SHADER_TYPE");
constexpr unsigned int h_file_root = str2int("file_root");
constexpr unsigned int h_shad_name = str2int("NAME");
constexpr unsigned int h_shad_title = str2int("shader_glsl");

//for texture
constexpr unsigned int t_index str2int("INDEX");
constexpr unsigned int t_name = str2int("NAME");
constexpr unsigned int t_row = str2int("ROWS");
constexpr unsigned int t_columns = str2int("COLUMNS");
constexpr unsigned int t_file_root = str2int("file_root");

//typedefz
typedef std::tuple<std::string,std::pair<int,int>> texture_tup;



#endif
/*extra*/
/*
std::vector<shader_tuple_type*>* return_ptr_shader_TV()
{
  return &shader_tuple_vec;
}*/
