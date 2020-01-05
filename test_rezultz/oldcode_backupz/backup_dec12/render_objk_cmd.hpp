
#pragma once

#include "geometry.hpp"
#include "pre_comb_objz.hpp"

#include <type_traits>

#define MAX_LVEL 23

struct lvel_data_struct
{


  //private :

};
//typedef std::tuple<std::string,std::>
const std::string "SHIP_A3";

class Resource_mgmt
{
  std::unordered_map<std::string,<std::string>>
  public :
  bool read_level_file(char* path);

  int parse_obj_list()
  {
    std::ifstream shader_config("shaderglsl/file_list_shader.xml");
    std::string file_in_string;
    shader_config.seekg(0, std::ios::end);
    file_in_string.reserve(shader_config.tellg());
    shader_config.seekg(0, std::ios::beg);
  }

};


class obj_cmder
{
  private :
  unsigned int id;
  std::array<lvel_data_struct,MAX_LVEL> lvel_array;

  public :

  void gl_run_render(GLFWwindow* glfwwindow, std::vector<gl_shader_t*>& in_shaderz,lvel_data_struct* lvel_active)
  {


    //std::cout <<"\n ###nummof shaders to process" << in_shaderz.size() << "  num of objket packagez::" << vetex_array_objkz.size() << '\n' << '\n';
  float timeValue = glfwGetTime();
  float sin_green = sin(timeValue);
  float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
  float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);

  for (size_t i =0; i<in_shaderz.size();i++)
  {
    in_shaderz.at(i)->use_shader();
  //  int vertexColorLocation = glGetUniformLocation(in_shaderz.at(i)->program_ID, "ourColor");
    //std::cout << "vertex_colour_unform at::" << vertexColorLocation << "  Progamid::"
          //    << in_shaderz.at(i)->program_ID << "ourColor" << '\n';
  //  std::vector<GLuint> vao_vec  =  vetex_array_objkz.at(i);
  //  glUniform4f(vertexColorLocation, sin_tsnz, sin_green, colour_angluretime, 1.f);

  }}




};


void switch_draw_syle(P_Render_STYZ in_style)
{
  GLint polygonMode;
  glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

GLint nstlz =  to_integral(in_style);
if(nstlz!=polygonMode)
{
  if(in_style ==P_Render_STYZ::WIREFRAME)
     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
  else if(in_style==P_Render_STYZ::FILL)
     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
  else
     glPolygonMode( GL_FRONT_AND_BACK, GL_POINTS);
}


}
