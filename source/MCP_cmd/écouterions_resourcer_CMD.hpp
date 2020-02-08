


#pragma once
//écoute 	écoutera 	écoutait //écouterait /écoutât

#include "../basez/rez_utility_lib.hpp"
#include "shader_pipeline_CMD.hpp"
#include "mcp_lib.hpp"


  class texture_ecouter : public singleton_exd
{
  protected :

  std::unordered_map<unsigned int,std::shared_ptr<texture_2>> texture_map;
  //or

  public :

  inline int registar_texture(int index,texture_2& in_texture)
  {
    texture_map.insert(std::make_pair(index,in_texture));
  }

};

class shader_ecouter : public singleton_exd
{
  protected :
  std::unordered_map<unsigned int,std::shared_ptr<gl_shader_t>> shader_map;
  //or
  std::unordered_map<unsigned int,std::shared_ptr<shader_default>> defl_shdr_map;

  inline int registar_texture(unsigned int index,std::shared_ptr<gl_shader_t> in_texture)
  {
    shader_map.insert(std::make_pair(index,in_texture));
  }

  inline int registar_texture(unsigned int index,std::shared_ptr<shader_default> in_texture)
  {
    defl_shdr_map.insert(std::make_pair(index,in_texture));
  }


};

struct path_handler{

  std::unordered_map<unisgned int,std::string_view>
};

  struct rez_cmd
  {
    public :
    texture_ecouter texture_ecouterait;
    shader_ecouter  shader_ecouterait

    shader_pipeline_CMD shpipe_cmd;
    texture_xml_lister t_xml_lister;



    void preform_texturexml_scan(std::string_view in_sv_xmlpath)
    {
      t_path_map* t_path_m_ptr;

      int parsSTATUS = t_xml_lister.load_run(in_sv_xmlpath);

      if(parsSTATUS<0)
      {
          std::cerr << "parseerror::" << parsSTATUS << '\n';
          return;
      }

      t_path_m_ptr = t_xml_lister.pointer_mapreturn();
      gen_texture_from_tt(t_path_m_ptr);


    }

    void gen_texture_from_tt(t_path_map* t_path_m_ptr)
    {
      
    }

  };
