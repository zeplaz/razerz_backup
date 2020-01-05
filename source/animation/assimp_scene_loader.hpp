#pragma once
const int WEIGHTS_PER_VERTEX = 4;


#include "animated_mesh.hpp"



class animated_mesh_loader{

  private :
  std::vector<joint> joints;
  std::vector<animated_mesh> meshes;
  std::vector<aiNode*> ai_nodez;
  std::vector<aiNodeAnim*> ai_node_animz;
  void recursive_node_process(aiNode* node);
  void anim_node_process();
  
  void recursive_processing(aiNode* node, const aiScene* scene);
  void process_mesh(aiMesh* mesh const aiScene* scene);
  unsigned int load_texture(const char* path);
  public :

  ~animated_mesh_loader();
  std::vector<animated_mesh*>&get_meshes();
  std::vector<animated_mesh> move_meshes();
  joint* find_joint(std::string name)
  {
    for(size_t i=0; i<joints.size();i++)
    {
      if(joints.at(i).joint_name ==name)
      return &joints.at(i);
    }
    return nullptr;
  }

  aiNode* find_ai_node(std::string name)
  {
    for(size_t i =0; i<ai_node.size();i++)
    {
      if(ai_nodes.at(i)->mName.data == name)
      return ai_nodes.at(i);
    }
    return nullptr;
  }


};
