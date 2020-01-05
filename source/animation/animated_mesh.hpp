#pragma once

//#include "assimp_scene_loader.hpp"

#include "skeleton.hpp"
#include "basez/shader_parser.hpp"

struct am_vertex_data{
  glm::vec4 position;

  glm::vec3 normal;
  glm::vec2 uv;
  glm::vec3 tangent;
  glm::vec4 colour;

  glm::vec4 jointIDs;
  glm::vec4 weights;

  unsigned int  meterialID;
};


struct  texture_data{
	unsigned int id;
	unsigned int type;
};


class animated_mesh
{
  private :
  std::vector<am_vertex_data> vertex_data;
  std::vector<texture_data> textures;
  std::vector<unsigned int> indices;
  std::array<GLuint,7> attrb_loc;

  GLuint joint_uniform_loc;
  GLuint am_VAO;
  GLuint am_VBO;
  GLuint am_IND;

  //joint joint_heirarchy;
  skeleton scene_skeleton;

  public :
  void set_attrabute_locations(unsigned int prog_ID);

  ~animated_mesh();
  animated_mesh(std::vector<am_vertex_data>* vd, std::vector<unsigned int>* indic,std::vector<texture_data> texdat);

  void init();
  void draw(gl_shader_t* shader);

  void buff_setup();


};
