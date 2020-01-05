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

#include "gl_lib_z.hpp"

typedef std::tuple<unsigned int,
           shader_type,std::string,std::string> shader_tuple_type;

static std::vector<shader_tuple_type*> shader_tuple_vec;


int run_parse();
shader_tuple_type* return_new_shader_tuple();
void size_of_tuplevec();
std::vector<shader_tuple_type*>* return_ptr_shader_TV();

class gl_shader_t
{
  private :
  shader_type contained_shaders=shader_type::SHADER_NULL;
  unsigned char shader_flags;
  std::map<int,std::pair<shader_type,std::string>> shader_code_map;
  std::map<int,std::pair<shader_type,GLuint>> shader_IDz_map;

  public :
  GLuint program_ID = 0;
  int Global_shader_ID = 0;
  std::unordered_map<std::string,GLuint> uniform_loc_map;
  //const_iterator

  void shutdown()
  {
    glDeleteShader(program_ID);
  }
  void set_glm_mat4(const std::string &name,const glm::mat4 &mat) const
  {
     glUniformMatrix4fv(glGetUniformLocation(program_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void add_uniform(std::string name,GLuint uniform_loc)
  {
    uniform_loc_map.insert(std::make_pair(name,uniform_loc));
  }
  GLuint return_uniform(std::string name)
  {
    auto shearcher = uniform_loc_map.find(name);
    if(shearcher!=uniform_loc_map.end())
    {
      return shearcher->second;
    }
    else{
      std::cerr <<"funtimez uniform not found goina cazedoom!";
      return 254;
    }
  }
  bool create_link_program(std::vector<int>& to_attach_shaders)
  {
    program_ID = glCreateProgram();
    std::cout <<"shader# in to link" << to_attach_shaders.size() <<'\n';
    for (size_t i =0; i< to_attach_shaders.size(); i++)
    {
      int shader_index = to_attach_shaders.at(i);
      std::cout << "SHADER INDEX#:" << shader_index << '\n';
      auto it_sh_map = shader_IDz_map.find(shader_index);

      if (it_sh_map != shader_IDz_map.end())
      {
        std::pair<shader_type,GLuint> *temp_pair = &it_sh_map->second;
        glAttachShader(program_ID,temp_pair->second);
        std::cout <<"shader attached: ID " << temp_pair->second <<'\n';
      }
      else {std::cout << "#ERROR:Sfound no shader ID at that index\n";}
    }

    glLinkProgram(program_ID);
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
           if(!success)
           {
               glGetProgramInfoLog(program_ID, 1024, NULL, infoLog);
               std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: "  << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
               return false;
           }
           return true;
  }

  inline void use_shader()
  {
    glUseProgram(program_ID);
  }

  void create_shader(shader_type shad_type, int s_index);

  void setup_shader_code(shader_tuple_type* in_shader_tuple)
  {
    std::cout << "->Loading shader tuple into shader\n";

    int s_index        = std::get<0>(*in_shader_tuple);
    shader_type s_type = std::get<1>(*in_shader_tuple);
    std::string path   = std::get<2>(*in_shader_tuple);

    std::ifstream file(path);
    std::string ret = "";
    std::string line_buff ="";
    if(file.is_open())
    {
     ret= std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
     std::cout << ret;
     file.close();
    }

    std::pair data_pair = std::make_pair(s_type,ret);
    shader_code_map.insert(std::make_pair(s_index,data_pair));
    std::cout << "->COMLEATED shader tuple into shader\n";
    std::cout << "INDEXINFO:"  << s_index <<"\n \n";
    this->create_shader(s_type,s_index);
    this->load_complie(s_index);
  }

  void load_complie(int map_index)
  {
    GLchar* log_shader;
    std::cout << "compling newshader:\n";
    GLint complie_status;

    auto it_scm = shader_code_map.find(map_index);
    if (it_scm != shader_code_map.end())
    {
      std::pair<shader_type,std::string> code_pair =  it_scm->second;

      auto it_s_idz = shader_IDz_map.find(map_index);
      if (it_s_idz != shader_IDz_map.end())
            {
              std::pair<shader_type,GLuint>  temp_id_pair = it_s_idz->second;
              if (temp_id_pair.first == code_pair.first)
              {
                const GLchar*  sh_gl_code = code_pair.second.c_str();
                glShaderSource(temp_id_pair.second,1,&sh_gl_code,NULL);
                glCompileShader(temp_id_pair.second);
                glGetShaderiv(temp_id_pair.second, GL_COMPILE_STATUS, &complie_status);
                if(complie_status !=GL_TRUE)
                {
                  GLint logsize;
                  std::cout <<"falure to shader_compplie \n";
                  glGetShaderiv(temp_id_pair.second,GL_INFO_LOG_LENGTH,&logsize);
                  log_shader = new GLchar[logsize+1];

                  glGetShaderInfoLog(temp_id_pair.second, logsize, NULL, log_shader);
                  // Write the error to a log
                  std::cout << log_shader<< '\n';
                  delete log_shader;
                }
              }
              else {std::cout << "shader types do not match eep!\n";}

            }
            else { std::cout << "inviald index No opengl_shader in map perhaps forgot to gen one \n";}

    }
    else {std::cout <<"shader_code_map not found\n";}
    std::cout << "SHADER COMPLIED\n";
  }

  void test_flags()
  { //contained_shaders = shader_type::VERTEX_SHADER;
    std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders |= shader_type::FRAGMENT_SHADER;
    //std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders =contained_shaders& ~shader_type::VERTEX_SHADER;
  //  std::cout << "contaned flags:" << (int)contained_shaders;
    std::cout <<"\n \n";
  }

};

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
  void  set_attrabutes(GLuint&gl_prgm);

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
