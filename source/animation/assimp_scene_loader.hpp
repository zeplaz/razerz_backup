#pragma once


#include "animated_mesh.hpp"

#include "texture.hpp"

const int WEIGHTS_PER_VERTEX = 4;

constexpr  unsigned int  INVALID_MATERIAL = 0xFFFFFFFF;
constexpr BUFFNUM = 5;

template<typename T>
int array_size(T* array)
{
  return sizeof(array)/sizeof(array[0]);
//int len = *(&array+1)-array;
}




struct mesh_entity{
  mesh_entity()
  {
    num_indecz=0;
    base_vert = 0;
    base_index = 0;
    material_index= INVALID_MATERIAL;

  }
  unsigned int num_indecz;
  unsigned int base_vert;
  unsigned int base_index;
  unsigned int material_index;

};

struct vertex_joint_data{
  unsigned int IDz[WEIGHTS_PER_VERTEX];
  float j_weights[WEIGHTS_PER_VERTEX];
  vertex_joint_data()
  {
    reset();
  }

  void reset()
  {
    for(int i=0;i<array_size(IDz);i++)
    {
      IDz[i]=0;
      j_weights[i]=0.0;
    }
  }

  void add_joint_data(unsigned int joint_ID,float in_wieght)
  {
    for(unsigned int i=0;i<array_size(IDz);i++)
    {
      if(j_weights[i]==0.0)
      {
        IDz[i]= joint_ID;
        j_weights[i]=in_wieght;
        return;
      }
    }
    std::cerr << "more points then space.. doom";
    exit(2);
  }
};


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

  initmesh(unsigned int mesh_index,const aiMesh* paimesh,std::vector<glm::vec3> pos,
          std::vector<glm::vec3> normals, std::vector<glm::vec2> tx_cord,
          std::vector<vertex_joint_data> jointz,std::vector<unsigned int> indicez)
          {
            const aiVector3D zero3d(0.0f,0.0f,0.0f);
            for(unsigned int i=0;i<paimesh->mNumVertices;i++)
            {
              const aiVector3D*  aipos    = &(paimesh->mVertices[i]);
              const aiVector3D* ainorm    = &(paimesh->mNormals[i]);
              const aiVector3D* aitexcord = paimesh->HasTextureCoords(0) ? &(paimesh->mTextureCoords[0][i]) : &zero3d;

              pos.push_back();
              normals.push_back();

            }
          }



  void load_mesh(std::string file_name,bool manual_texture)
  {
    GLuint vao_msh;
    GLuint buffers[BUFFNUM];
    const aiScene* ai_scene;
    Assimp::Importer assip_importer;

    std::vector<mesh_entity> mesh_entries;
    std::vector<Texture*> textures_vec;

    Matrix4f glob_inverse_tranz;

    glGenVertexArrays(1, &vao_constexpr BUFFNUM = 5;msh);
    glBindVertexArray(vao_msh);

    glGenBuffers(array_size(buffers),buffers);
    bool ret = false;
    ai_scene = assip_importer.ReadFile(file_name.c_str(),aiProcess_Triangulate
                                      | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if(ai_scene)
    {
      glob_inverse_tranz = ai_scene->mRootNode->mTransformation;
      glob_inverse_tranz.Inverse();
      ret= init_ai_scene(ai_scene,file_name,manual_texture);
    }
  }

  bool init_ai_scene(const aiScene* in_scene,const std::string& file_name,bool& manual_texture)
  {
    mesh_entries.resize(in_scene->mNumMeshes);
    textures_vec.resize(in_scene->mNumMaterials);

    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> text_cord;
    std::vector<vertex_joint_data> jointz;
    std::vector<unsigned int> indicez;
    unsigned int num_verx  =0;
    unsigned int num_indicz=0;

    for(unsigned int i=0;i<mesh_entries.size();i++)
    {
      mesh_entries[i].material_index=in_scene->mMeshes[i]->mMaterialIndex;
      mesh_entries[i].num_indecz    =in_scene->mMeshes[i]->mNumFaces * 3;
      mesh_entries[i].base_vert     =num_verx;
      mesh_entries[i].base_index    =num_indicz;

      num_verx   +=in_scene->mMeshes[i]->mNumVertices;
      num_indicz +=mesh_entries[i].num_indicz;
    }

    pos.reserve(num_verx);
    normal.reserve(num_verx);
    text_cord.reserve(num_verx);
    jointz.reserve(num_verx);
    indicez.reserve(num_verx);

    for(unsigned int i =0;i<mesh_entries.size();i++)
    {
      const aiMesh* paimesh = in_scene->mMeshes[i];
      initmeshz(i,paimesh,pos,normal,text_cord,jointz,indicez);
    }
    if(manual_texture == false)
    {
      if(!assip_materials(in_scene, file_name))
    {
      return false;
    }
    }

  }

  assip_materials(const aiScene* in_scene, const std::string& filename)
  {
    std::string::size_type string_index = filename.find_last_of("/");
    std::string metr_string;
    if(string_index==std::string::npos)
    {
      metr_string = ".";
    }
    else if (string_index==0)
    {
      metr_string = "/";
    }
    else
    {
      metr_string = filename.substr(0,string_index);
    }
    bool ret = true;
    for(unsigned int i =0; i<in_scene->mNumMaterials; i++)
    {
      const aiMaterial* assip_material = in_scene->mMaterials[i];
      textures_vec[i]=NULL;
      if(assip_material->GetTextureCount(aiTextureType_DIFFUSE)>0)
      {
        aistring path;
        if(assip_material->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
        {
          std::string p(path.data);
          if(p.substr(0,2)==".\\")
            {
              p = p.substr(2,p.size()-2);

            }

      }
    }
  }
}

};
