
#pragma once

#include "geometry.hpp"
#include "pre_comb_objz.hpp"
#include "model_parser.hpp"



struct Phong_reflection
{
  //ambient light
  glm::vec4 ambient;
  glm::vec4 spot_cone_drection;

//directiona light
float drectional_srength;

//Point light
float const_attenuation;
float quadr_attenuation;
float linear_attenuation;

//spot light

  float spot_cos_cutoff;
  float spot_exponent;

  //
  float gamma_c;
};

struct light_propertyz
{
  glm::vec4 position;
  glm::vec4 intensity;

  bool is_enabled;

  Phong_reflection phong_light;
  int  Light_type;
};


class gl_lightzctl
{
  public :
  std::vector<light_propertyz> light_list;

  size_t test_size()
  {
    std::cout << "lightpropy struct size::" << sizeof(light_propertyz)
    << "\n is multiof vec4:" << sizeof(light_propertyz)/sizeof(glm::vec4) <<'\n';

    return sizeof(light_propertyz);
    }

  void set_ambient(glm::vec4 amb)
  {
    light_propertyz light_proper;
    light_proper.is_enabled = true;
    light_proper.Light_type =L_AMBIENT;

    light_proper.phong_light.ambient = amb;

    light_list.push_back(light_proper);
  }

  void set_light_diffuse(glm::vec4 lpos,glm::vec4 intezy,
                          float d_strgth)
  {
    light_propertyz light_proper;
    light_proper.is_enabled = true;
    light_proper.Light_type  =L_DIFFUSE;

    light_proper.position    =lpos;
    light_proper.intensity   =intezy;
    light_proper.phong_light.drectional_srength=d_strgth;

    light_list.push_back(light_proper);
  }

  void set_light_point(std::array<float,3> attenuation,glm::vec4 lpos,
    glm::vec4 intezy,float strenth)
  {
    light_propertyz light_proper;
    light_proper.is_enabled = true;
    light_proper.Light_type  =L_POINT;

    light_proper.position =lpos;
    light_proper.phong_light.drectional_srength =strenth;

    light_proper.phong_light.const_attenuation = attenuation[0];
    light_proper.phong_light.quadr_attenuation = attenuation[1];
    light_proper.phong_light.linear_attenuation= attenuation[2];

    light_list.push_back(light_proper);
  }

  void set_light_spot(std::array<float,3> annut,glm::vec4 lpos, glm::vec4 intezy,glm::vec4 cone_dir,
                        float cos_cutoff,float exp,float catten)
  {
    light_propertyz light_proper;
    light_proper.is_enabled = true;
    light_proper.Light_type                    =L_SPOT;

    light_proper.position                      =lpos;
    light_proper.intensity                     =intezy;
    light_proper.phong_light.const_attenuation =catten;
    light_proper.phong_light.spot_exponent     =exp;
    light_proper.phong_light.spot_cos_cutoff   =cos_cutoff;
    light_proper.phong_light.spot_cone_drection=cone_dir;

    light_proper.phong_light.const_attenuation = annut[0];
    light_proper.phong_light.quadr_attenuation = annut[1];
    light_proper.phong_light.linear_attenuation= annut[2];

    light_list.push_back(light_proper);
  }
};


class scene{

  private :
  std::unordered_map<Scene_Mesh_RDR,gl_shader_t*> shader_map;
  std::unordered_map<Scene_Mesh_RDR,gl_lightzctl> light_crt_map;
  std::unordered_map<Scene_Mesh_RDR,view_lenz*> lenz_map;

  std::multimap<Scene_Mesh_RDR,mesh*> mesh_multi_map;
  std::multimap<Scene_Mesh_RDR,model*> model_multi_map;

  typedef std::multimap<Scene_Mesh_RDR, mesh*>::iterator MMAPIterator;
  typedef std::multimap<Scene_Mesh_RDR, model*>::iterator model_iterator;
  typedef std::unordered_map<Scene_Mesh_RDR,gl_shader_t*>::const_iterator SHAD_Iter;
  typedef std::unordered_map<Scene_Mesh_RDR,view_lenz*>::const_iterator LENZ_Iter;
  typedef std::unordered_map<Scene_Mesh_RDR,gl_lightzctl>::iterator LIGHT_Iter;

  public :

  offset_table of_table;
  GLuint lightA1_buffer_ID;
  GLuint prsiz_lightA1_buffer_ID;

  gl_lightzctl* reutrn_prt_scene_lightcrl(Scene_Mesh_RDR at_scene)
  {
    LIGHT_Iter li_it = light_crt_map.find (at_scene);
   if ( li_it == light_crt_map.end())
   {
     std::cerr <<"#!!ligth_arrgment not foundz\n";
   }
   else
   {
     return   &li_it->second;
  }
  }

  void light_data_size(Scene_Mesh_RDR at_scene,size_t& out_num_lightz,size_t& out_data_size)
  {

    size_t total_lightsize=0;

  LIGHT_Iter li_it = light_crt_map.find (at_scene);
   if ( li_it == light_crt_map.end())
   {
     std::cerr <<"#!!ligth_arrgment not foundz\n";
   }
   else
   {
    gl_lightzctl* light_scene_ptr=   &li_it->second;
    out_num_lightz = light_scene_ptr->light_list.size();
    for(size_t i =0; i<out_num_lightz;i++)
    {
      total_lightsize+=sizeof(light_scene_ptr->light_list.at(i));
    }
    out_data_size =total_lightsize;
    //light_scene_ptr->update_lightz();
    //light_scene_ptr->pass_datato_shader(current_shader);
  }

    std::cout << "\n ################# \n totalsize_lightz::" << total_lightsize <<'\n'
    << "numlightz" << out_num_lightz <<'\n' <<"is a multiof 4:"<< (total_lightsize/out_num_lightz)/4 <<'\n';

  }
  void insert_shader(Scene_Mesh_RDR scene,gl_shader_t* in_shdr)
  {
    shader_map.insert(std::make_pair(scene,in_shdr));
  }

  void insert_light_ctler(Scene_Mesh_RDR scene,gl_lightzctl in_light)
  {
    light_crt_map.insert(std::make_pair(scene,in_light));
  }

  void insert_model(Scene_Mesh_RDR scene,model* in_model)
  {
    model_multi_map.insert(std::make_pair(scene,in_model));
  }

  void insert_lenz(Scene_Mesh_RDR scene,view_lenz* in_lenz)
  {
    lenz_map.insert(std::make_pair(scene,in_lenz));
  }

  void insert_mesh(Scene_Mesh_RDR scene,mesh* in_mesh)
  {
    mesh_multi_map.insert(std::make_pair(scene,in_mesh));
  }


  void lightsetup()
  {
    size_t abentoffiset = of_table.l_offset.l_amb;
    size_t light_num;
    size_t light_data_size;
    this->light_data_size(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01,light_num,light_data_size);
    gl_lightzctl* light_ctrler =  this->reutrn_prt_scene_lightcrl(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01);

    glCreateBuffers(1, &lightA1_buffer_ID);
    glCreateBuffers(1, &prsiz_lightA1_buffer_ID);
    glNamedBufferStorage(lightA1_buffer_ID, light_data_size, light_ctrler->light_list.data(),GL_MAP_UNSYNCHRONIZED_BIT| GL_MAP_WRITE_BIT);
    //glNamedBufferStorage(prsiz_lightA1_buffer_ID, light_data_size, light_ctrler->light_list.data(),GL_MAP_UNSYNCHRONIZED_BIT|GL_DYNAMIC_STORAGE_BIT |GL_MAP_WRITE_BIT|GL_MAP_COHERENT_BIT|GL_MAP_PERSISTENT_BIT);
        //

  }

void draw_scene(Scene_Mesh_RDR to_draw_scene)
{
  gl_shader_t* current_shader;
  view_lenz* active_lenz;

   SHAD_Iter s_it = shader_map.find(to_draw_scene);
   if ( s_it == shader_map.end())
   {
     std::cerr <<"#!!scene_shader not foundz\n";
   }
   else
   {
     current_shader=s_it->second;
     current_shader->use_shader();
   }
   LENZ_Iter lez_it= lenz_map.find (to_draw_scene);
    if ( lez_it == lenz_map.end())
    {
      std::cerr<< "#!!scen_lenz not foundz\n";
    }
    else
    {
      active_lenz=lez_it->second;
    }
//setuo matrixz
  glm::mat4 active_projection = active_lenz->lenz_projection();
  glm::mat4 active_view       = active_lenz->return_lenz_view();

//pass light unifrmz or data..
if(Scene_Mesh_RDR::BASIC_SHADER_SCENE01 !=to_draw_scene)
{
  LIGHT_Iter li_it = light_crt_map.find (to_draw_scene);
 if ( li_it == light_crt_map.end())
 {
   std::cerr <<"#!!ligth_arrgment not foundz\n";
 }
 else
 {
  gl_lightzctl* light_scene_ptr=   &li_it->second;
  //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, prsiz_lightA1_buffer_ID);
  float timeValue = glfwGetTime();
  float sin_green = sin(timeValue);
  float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
  float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);
  glm::vec4 ambenshift =glm::vec4(colour_angluretime,sin_green,sin_tsnz,1);
  //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, lightA1_buffer_ID);
  //light_scene_ptr->update_lightz();
  //light_scene_ptr->pass_datato_shader(current_shader);
}}

std::pair<MMAPIterator, MMAPIterator> result_mesh = mesh_multi_map.equal_range(to_draw_scene);

for (MMAPIterator it = result_mesh.first; it != result_mesh.second; it++)
{
 mesh* mesh_ptr = it->second;
 mesh_ptr->draw(current_shader,active_view,active_projection);
}

//model drawz
std::pair<model_iterator, model_iterator> result_model = model_multi_map.equal_range(to_draw_scene);

for (model_iterator it = result_model.first; it != result_model.second; it++)
{
 model* model_ptr = it->second;
 model_ptr->model_draw(current_shader,active_view,active_projection);
}

}

};
