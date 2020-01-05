
#include "joint.hpp"


joint::joint(animated_mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat)
{
  id =in_id;
  joint_name = in_name;
  offset_matrix = AiToGLMMat4(in_o_mat);
  a_mesh = in_mesh;
  parent_joint = nullptr;

}
joint::joint(animated_mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat)
{
  id =in_id;
  joint_name = in_name;
  offset_matrix = in_o_mat;
  a_mesh = in_mesh;
  parent_joint = nullptr;
}


glm::mat4 joint::get_parent_transform()
{
  joint* temp_joint = parent_joint;
  std::vector<glm::mat4> matz;

  while(temp_joint !=nullptr)
  {
    glm::mat4 temp_mat = AiToGLMMat4(temp_joint->assimp_node->mTransformation);
    matz.push_back(temp_mat);
    temp_joint = temp_joint->parent_joint;
  }
  glm::mat4 concat_tranz;
  for(size_t i =matz.size()-1; i>0; i--)
  {
    concat_tranz *=matz.at(i);
  }
  return concat_tranz;
}

  unsigned int joint::find_pos(float time)
  {
    for(unsigned int i =0; i<anim_node->mNumPositionKeys-1;i++)
    {
      if(time<(float) anim_node->mPositionKeys[i + 1].mTime)
      return i;
    }
    return 0;
  }

  glm::vec3 joint::calc_interpolate_pos(float time)
  {
    if(anim_node->mNumPositionKeys == 1)
    {
      aiVector3D assimp_val = anim_node->mPositionKeys[0].mValue;
      glm::vec3 val(assimp_val.x,assimp_val.y,assimp_val.z);
     return val;
    }

    unsigned int PositionIndex = find_pos(time);
    unsigned int NextPositionIndex = (PositionIndex + 1);

    float delta_time = anim_node->mPositionKeys[NextPositionIndex].mTime -
    anim_node->mPositionKeys[PositionIndex].mTime;

    float factor = (time - (float)anim_node->mPositionKeys[PositionIndex].mTime)/delta_time;
    const aiVector3D StartPosition = anim_node->mPositionKeys[PositionIndex].mValue;
    const aiVector3D EndPosition   = anim_node->mPositionKeys[NextPositionIndex].mValue;

    glm::vec3 val = glm::mix(p1,p2,factor);
    return val;
  }

  unsigned int joint::find_rotation(float time)
  {
    for(unsigned int i = 0 ; i < anim_node->mNumRotationKeys - 1 ; i++)
    {
      if(time<(float)anim_node->mRotationKeys[i + 1].mTime)
             return i;
    }
    return 0;
    }

  glm::quat joint::calc_interpolate_rotation(float time)
  {
    if(anim_node->mNumRotationKeys == 1)
    {
      aiQuaternion assimp_val = anim_node->mRotationKeys[0].mValue;
      glm::quat val(assimp_val.w,assimp_val.x,assimp_val.y,assimp_val.z);
         return val;
    }

    unsigned int RotationIndex = find_rotation(time);
    unsigned int NextRotationIndex = (RotationIndex + 1);

    float delta_time = anim_node->mRotationKeys[NextRotationIndex].mTime -
    anim_node->mRotationKeys[RotationIndex].mTime;

    float factor = time - (float)anim_node->mRotationKeys[RotationIndex].mTime/delta_time;

    const aiQuaternion& StartRotationQ =anim_node->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   =anim_node->mRotationKeys[NextRotationIndex].mValue;
    glm::quat r1(StartRotationQ.w,StartRotationQ.x,StartRotationQ.y,StartRotationQ.z);
    glm::quat r2(EndRotationQ.w,EndRotationQ.x,EndRotationQ.y,EndRotationQ.z);
    glm::quat val = glm::slerp(r1,r2,factor);
     return val;
  }



  void joint::update_key_fame_transform(float time)
  {
    if(anim_node == nullptr)
    return;

    pos = calc_interpolate_pos(time);
    qutanario_rotate = calc_interpolate_rotation(time);
    scale = glm::vec3(1.0);

    glm::mat4 out_mat;
    out_mat *= glm::translate(glm::mat4(1.0f),pos);
    out_mat *= glm::mat4_cast(qutanario_rotate);
    out_mat *= glm::scale(glm::mat4(1.0f),scale);

    assimp_node->mTransformation = GLMMat4ToAi(out_mat);
  }
