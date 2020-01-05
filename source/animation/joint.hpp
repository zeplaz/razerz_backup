
#pragma once
#include <list>

#include "animation.hpp"

class skeleton;
class animated_mesh;
class Animation;
class sym_object;

class joint
{
  private :
  int id;
  std::list<joint> decedence;
  glm::mat4 transform;

  public :
  std::string joint_name;

  animated_mesh* a_mesh;

  aiNode* assimp_node;
  aiNodeAnim* anim_node;

  joint* parent_joint;
  skeleton* parent_skeleton;

  glm::vec4 parent_transform;
  glm::mat4 offset_matrix;

  //keyframeo
  glm::vec3 pos;
  glm::quat qutanario_rotate;
  glm::vec3 scale;
  glm::vec3 p1;
  glm::vec3 p2;

  unsigned int find_pos(float time);
  glm::vec3 calc_interpolate_pos(float time);
  unsigned int find_rotation(float time);
  glm::quat calc_interpolate_rotation(float time);

  joint(){joint_name ="";}
  joint(animated_mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
  joint(animated_mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

  void update_key_fame_transform(float time);
  glm::mat4 get_parent_transform();
};


static aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat)
{
     return aiMatrix4x4(mat[0][0],mat[0][1],mat[0][2],mat[0][3],
                        mat[1][0],mat[1][1],mat[1][2],mat[1][3],
                        mat[2][0],mat[2][1],mat[2][2],mat[2][3],
                        mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
}

static glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat)
{
      glm::mat4 tmp;
      tmp[0][0] = in_mat.a1;
      tmp[1][0] = in_mat.b1;
      tmp[2][0] = in_mat.c1;
      tmp[3][0] = in_mat.d1;

      tmp[0][1] = in_mat.a2;
      tmp[1][1] = in_mat.b2;
      tmp[2][1] = in_mat.c2;
      tmp[3][1] = in_mat.d2;

     tmp[0][2] = in_mat.a3;
     tmp[1][2] = in_mat.b3;
     tmp[2][2] = in_mat.c3;
     tmp[3][2] = in_mat.d3;

     tmp[0][3] = in_mat.a4;
     tmp[1][3] = in_mat.b4;
     tmp[2][3] = in_mat.c4;
     tmp[3][3] = in_mat.d4;
     return tmp;
}
