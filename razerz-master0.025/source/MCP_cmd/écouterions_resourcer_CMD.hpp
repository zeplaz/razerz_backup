
#pragma once
//écoute 	écoutera 	écoutait //écouterait /écoutât


#include "mcp_lib.hpp"
#include "periphery_input.hpp"

template<auto VFnPtr> struct
wrapper;

template<typename TResult, typename... TArgs, TResult ( * VFnPtr)(TArgs...)>
struct wrapper<VFnPtr>
{
    TResult
    operator ()(TArgs... args) const noexcept(noexcept((*VFnPtr)(::std::forward<TArgs>(args)...)))
    {
        return (*VFnPtr)(::std::forward<TArgs>(args)...);
    }
};

/*
struct path_handler{
  std::unordered_map<unsigned int,std::string_view>
};*/



/*
symid,priotry,blockID,drawfunc,ptr_paramz;
typedef int Block_ID;
std::<>
typedef std::priority_queue<,>;

typedef std::multimap<Block_ID,wrapper>;
*/
//template<classType>

class Emetteur
{
  public :
  constexpr static  double D_ZERO = 0.0;
  inline static double Current_Time= D_ZERO;
  float delta_time;

  void update_clock(double in_time)
  {
    Current_Time =in_time;
  }
}

template<class Listed, typename pak>
  class ecouter
{
  protected :

  //std::priority_queue<>
//  std::mutlimap<unigned int,>
  void input_event();
  std::vector<pak> pack_arry;
  std::unordered_map<unsigned int,std::shared_ptr<Listed>> listed_map;
  //or
  //std::unordered_map<unsigned int,std::shared_ptr<gl_shader_t>> shader_map;
  //or
  ///std::unordered_map<unsigned int,std::shared_ptr<shader_seprate>> separated_shdr_prgm_map;
  //std::unordered_map<unsigned int,std::shared_ptr<>> shdr_prgm_map;
  //std::unordered_map<unsigned int,,std::shared_ptr<>> pipeline_map;

  public :

  inline int add_pak(pak& in_trp)
  {
    pack_arry.push_back(in_trp);
    return pack_arry.size()-1;
  }
  inline unsigned int registar_ojk(std::shared_ptr<Listed> in_obj)
  {
    listed_map.insert(std::make_pair(in_obj->get_id(),in_obj));
    return in_obj->get_id();
  }
    /*template<class func, class obj>
    void (*callback_setter) (func in_func,obj in_obj)
    {

    }*/
  /*

  inline unsigned int registar_shader(std::shared_ptr<Listed> in_shader)
  {

    shader_map.insert(std::make_pair(in_shader->get_id(),in_shader));
      return in_shader->get_id();
  }

  inline unsigned int registar_separated_shader(std::shared_ptr<shader_seprate> in_shader)
  {

    separated_shdr_prgm_map.insert(std::make_pair(in_shader->get_id(),in_shader));
    return in_shader->get_id();
  }
*/
};


struct rez_mgmt
{
  public :

  ecouter<text_render_glyph,character>  ecouterait_glyph;
  ecouter<terrain,terrain_feture_tupl>  ecouterait_terrain;
  ecouter<std::shared_ptr<shader_seprate>,terrain_feture_tupl>  ecouterait_terrain;

  Emetteur emetteur;

  std::array<view_lenz,6> lenz_array;
  view_lenz* prim_lenz;
  priphery_compoent priphery_input;
  //  shader_pipeline_CMD shpipe_cmd;
  //texture_xml_parser t_xml_parser;
};

inline static rez_mgmt* global_r_mgmt=nullptr;


/*

class shader_ecouter : public singleton_exd
{
  protected :


  inline int registar_texture(unsigned int index,std::shared_ptr<gl_shader_t> in_texture)
  {
    shader_map.insert(std::make_pair(index,in_texture));
  }


};*/

  /*  void preform_texturexml_scan(pathz& in_path)
    {
      //t_path_map* t_path_m_ptr;

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

    }*/
