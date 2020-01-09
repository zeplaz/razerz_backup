#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <map>

#include "gl_lib_z.hpp"

typedef std::tuple<unsigned int,
           shader_type,std::string,std::string> shader_tuple_type;

//static std::vector<shader_tuple_type*> shader_tuple_vec;
static std::map<unsigned int,shader_tuple_type*> shader_tuple_map;

shader_tuple_type* return_new_shader_tuple();
std::map<unsigned int,shader_tuple_type*>* return_shdrmap_ptr_TV();
void size_of_tuplevec();
int run_parse();
//std::vector<shader_tuple_type*>* return_ptr_shader_TV();








/*
DEPREATED SHADER CLASS>..?
*/

class gl_shader
{
  private :
  std::string shader_code_vertex;
  std::string shader_code_fragment;
  shader_type s_type;
  public :
  GLuint program_ID = 0;
  GLuint shader_pos;
  GLuint shader_colour;

  GLuint vertex_shader_ID;
  GLuint frag_shader_ID;

  void create_shader(shader_type shad_type);
  void get_shader_code(const std::string &path,shader_type type);
  void load_shader_complie();
  void set_attrabutes(GLuint&gl_prgm);

  inline void use_shader()
  {
    glUseProgram(program_ID);
  }

  inline void get_strd_shader_code(std::string in_path,shader_type type)
  {
   if(type ==shader_type::VERTEX_SHADER)
    {
      shader_code_vertex = in_path;
    }

   else if(type ==shader_type::FRAGMENT_SHADER)
     {
       shader_code_fragment = in_path;
     }
     s_type = type;
  }
};
