#include "scene.hpp"


template<typename Inher_type>
class singleton
{
  protected :
  singleton() = default;

  public :
  singleton(const singleton&) = delete;
  singleton &operator = (const singleton&)=delete;

  static Inher_type &get_instance()
  {
    static Inher_type instance;
    return instance;
  }
};






class scene_CMDer : public singleton<scene_CMDer>
{

  public :
  scene active_scene;
  //std::unordered_map<std::string,model_ajustment> model_ajust_map;


 void passthrough_lighting(Scene_Mesh_RDR scene,gl_lightzctl in_light)
 {
   active_scene.insert_light_ctler(scene,in_light);
 }


 void passthrough_lenz(Scene_Mesh_RDR scene,view_lenz* in_lenz)
 {
   active_scene.insert_lenz(scene,in_lenz);
 }

  bool load_scene_shaders()
  {

    /*
    * SHADER SETUPZ
    */

    gl_shader_t* shader_3_basic= new gl_shader_t();
    gl_shader_t* shader_lightA01= new gl_shader_t();

    std::vector<gl_shader_t*> shader_prt_vec;

    shader_prt_vec.push_back(shader_3_basic);
    shader_prt_vec.push_back(shader_lightA01);

    //run paser
      int errcode = run_parse();

    shader_3_basic->test_flags();
    shader_lightA01->test_flags();

    //shader datastucz
    std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();
    std::vector<int> shdr_3_list;
    std::vector<int> shdr_lightA01_list;

//shader_setupz
    bool is_complie = true;
    std::cout <<"shader number" << shader_TV_ptr->size();
    shader_3_basic->setup_shader_code(shader_TV_ptr->at(1));
    shader_3_basic->setup_shader_code(shader_TV_ptr->at(0));
    shdr_3_list.push_back(SHD_BASICA02_VERTEX);
    shdr_3_list.push_back(SHD_BASIC_FRAG);

    shader_3_basic->create_link_program(shdr_3_list);
    shader_3_basic->test_flags();

    shader_lightA01->setup_shader_code(shader_TV_ptr->at(2));
    shader_lightA01->setup_shader_code(shader_TV_ptr->at(3));

    shdr_lightA01_list.push_back(SHD_LIGHTA1_VERTEX);
    shdr_lightA01_list.push_back(SHD_LIGHTA1_FRAG);

    is_complie =shader_lightA01->create_link_program(shdr_lightA01_list);
    shader_lightA01->test_flags();
  std::cout << "##SHADER settup COMPLEATE\n";
  if(is_complie == false)
  {
    return false;
  }
    active_scene.insert_shader(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01,shader_lightA01);
    active_scene.insert_shader(Scene_Mesh_RDR::BASIC_SHADER_SCENE01,shader_3_basic);

    shader_lightA01->use_shader();

    shader_lightA01->add_uniform("model_view",glGetUniformLocation(shader_lightA01->program_ID,"model_view"));
    shader_lightA01->add_uniform("model_proj_View",glGetUniformLocation(shader_lightA01->program_ID,"model_proj_View"));
    shader_lightA01->add_uniform("normal_matrix",glGetUniformLocation(shader_lightA01->program_ID,"normal_matrix"));

  return true;
  }

  void setup_scene_modelz()
  {

    /*
    working DATA for current test.
    */

    model_ajustment test_ajustship;
    model_ajustment test_ajustship2;

    test_ajustship.rotation_ajust = glm::vec3(0.f);
    test_ajustship.posz_ajust  = glm::vec3(0.f);
    test_ajustship.scale_ajust = glm::vec3(0.f);
    test_ajustship2.rotation_ajust = glm::vec3(0.f);
    test_ajustship2.posz_ajust  = glm::vec3(0.f);
    test_ajustship2.scale_ajust = glm::vec3(0.f);

    model_ajustment ship_2_orgin;

    ship_2_orgin.posz_ajust.x=0.9f;
    ship_2_orgin.posz_ajust.y=0.5f;
    ship_2_orgin.posz_ajust.z= -0.1f;

    ship_2_orgin.scale_ajust = glm::vec3(0.1f);
    ship_2_orgin.rotation_ajust.y = 120.f;
    ship_2_orgin.rotation_ajust.x = 0.f;
    ship_2_orgin.rotation_ajust.z = 0.f;


    model_ajust_map.insert(ship_A01,test_ajustship);
    model_ajust_map.insert(ship_A03,test_ajustship2);

    /*
    *meshsettup
    */

    std::cout <<"setupmeshz \n";
    wavefornt_parser2 wp2;

    std::string shipA2_path = {"data_extrn/ship_A3/boat_Base_2.obj"};
    std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
              std::shared_ptr<std::vector<unsigned int>>>
              shipA2_mesh_vertex_DATA = wp2.read_file(shipA2_path);

    mesh* shipA3 = new mesh();

    shipA3->init(shipA2_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
    shipA3->bindmesh_buf();

    glm::vec3 shipA2_emis            =glm::vec3(0.0f);
    glm::vec3 shipA2_amb_ref         =glm::vec3(0.5,0.6,0.8);
    glm::vec3 shipA2_diff_ref        =glm::vec3(0.5,0.3,0.3);
    glm::vec3 shipA2_spektral_reflect=glm::vec3(1.0,1.0,1.0);
    float     shipA2_shinyz          =600;

    shipA3->set_meterial(shipA2_emis,shipA2_amb_ref,shipA2_diff_ref,
                          shipA2_spektral_reflect,shipA2_shinyz);

    mesh* ship_basic = new mesh();
    ship_basic->init(shipA2_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
    ship_basic->bindmesh_buf();
    ship_basic->set_mesh_model_origin(ship_2_orgin);

    ship_basic->set_meterial(shipA2_emis,shipA2_amb_ref,shipA2_diff_ref,
                        shipA2_spektral_reflect,shipA2_shinyz);


  /*
  texture setuptest_move to mesh
  */

  std::cout << "load texturez\n";

    //vglLoadTexture("data_extrn/ship_base_A03.bmp");
  texture_paramz_pak ship_tex_A3_parmz;
  ship_tex_A3_parmz.wm_s    = WarpMode::REPEAT;
  ship_tex_A3_parmz.wm_t    = WarpMode::REPEAT;
  ship_tex_A3_parmz.mag     = Filter::LINEAR;
  ship_tex_A3_parmz.min     = Filter::LINEAR;
  ship_tex_A3_parmz.path    = "data_extrn/ship_A3/ship_base_A03.5.bmp";
  ship_tex_A3_parmz.channels= 3;
  ship_tex_A3_parmz.unform_name = "active_texture_sampler";
  ship_tex_A3_parmz.tex_unit_index = 0;
  ship_tex_A3_parmz.text_type_flag = M_Tex_Flag::TEXTYR_BASIC;

  texture_paramz_pak ship_tex_A3_normal_parmz;
  ship_tex_A3_parmz.wm_s    = WarpMode::REPEAT;
  ship_tex_A3_parmz.wm_t    = WarpMode::REPEAT;
  ship_tex_A3_parmz.mag     = Filter::LINEAR;
  ship_tex_A3_parmz.min     = Filter::LINEAR;
  ship_tex_A3_parmz.path    = "data_extrn/ship_A3/Ship_A3.05_hight_normal.bmp";
  ship_tex_A3_parmz.channels= 3;
  ship_tex_A3_parmz.unform_name = "normal_mapSampler";
  ship_tex_A3_parmz.tex_unit_index = 1;
  ship_tex_A3_parmz.text_type_flag = M_Tex_Flag::TEXTYR_NORMAL;

  shipA3.texture_setup(ship_tex_A3_parmz);
  shipA3.texture_setup(ship_tex_A3_normal_parmz);
  ship_basic.texture_setup(ship_tex_A3_parmz);



  active_scene.insert_mesh(Scene_Mesh_RDR::LIGHT_SHADER_SCENE01,shipA3);
  active_scene.insert_mesh(Scene_Mesh_RDR::LIGHT_SHADER_SCENE01,ship_basic);
  }

  void setup_scene_lighting()
  {

  }
  void init()
  {
    bool vaild = true;
    vaild  = this->load_scene_shaders();
    if(vaild==false)
    {
      exit(-1);
    }
    this->setup_scene_modelz();
  }



}
