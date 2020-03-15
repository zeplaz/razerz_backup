

#include "geometry.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class model{

 public:
   std::vector<mesh> model_meshez;
   std::string directory;
   bool gammaCorrection;

  model(char* path)
  {
    load_model(path);
  }
  void model_draw(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj)
  {
    for(size_t i=0; i<model_meshez.size();i++)
    {
      model_meshez[i].draw_element(shader,view,proj);
    }
  }


  private :


  void load_model(std::string path)
  {
    Assimp::Importer importer;
    const aiScene* aimp_scene = importer.ReadFile(path,
                                               aiProcess_Triangulate |
                                               aiProcess_FlipUVs| aiProcess_CalcTangentSpace);

    if(!aimp_scene || aimp_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aimp_scene->mRootNode)
    {
      std::cerr << "ERROR in ASSIMP LOAD::" << importer.GetErrorString() << '\n';
    }

    process_assimp_node(aimp_scene->mRootNode,aimp_scene);
  }


  void process_assimp_node(aiNode *node,const aiScene *scene)
  {
    std::cout<< "##BEGIN::ASSIMP nodeprocesr\n";
    for(size_t i=0;i<node->mNumMeshes;i++)
    {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      model_meshez.push_back(process_mesh(mesh,scene));
    }
  }

  mesh process_mesh(aiMesh *in_mesh, const aiScene *scene)
{
  std::cout << "##BEgin model Mesh Processing\n";
  std::vector<Texture_gl>   texturez;
  std::vector<mesh_vertex>  verticez;
  std::vector<unsigned int> indicez;

  for(size_t i =0;i<in_mesh->mNumVertices;i++)
  {
    mesh_vertex vertex;
    glm::vec3 vector;

    vector.x=in_mesh->mVertices[i].x;
    vector.y=in_mesh->mVertices[i].y;
    vector.z=in_mesh->mVertices[i].z;

    vertex.v_position=vector;

    vector.x=in_mesh->mNormals[i].x;
    vector.y=in_mesh->mNormals[i].y;
    vector.z=in_mesh->mNormals[i].z;

    vertex.v_normal=vector;
    if(in_mesh->mTextureCoords[0])
    {
      glm::vec2 vec;
      vec.x = in_mesh->mTextureCoords[0][i].x;
      vec.y = in_mesh->mTextureCoords[0][i].y;
      vertex.v_textcord = vec;
    }
    else
    {
      vertex.v_textcord = glm::vec2(0.0f,0.0f);
    }
    vector.x=in_mesh->mTangents[i].x;
    vector.y=in_mesh->mTangents[i].y;
    vector.z=in_mesh->mTangents[i].z;

    vertex.v_tangent;

    vector.x=in_mesh->mBitangents[i].x;
    vector.y=in_mesh->mBitangents[i].y;
    vector.z=in_mesh->mBitangents[i].z;

    vertex.v_bitagent;
    verticez.push_back(vertex);
  }
  for(size_t i=0;i<in_mesh->mNumFaces;i++)
  {
    aiFace face =in_mesh->mFaces[i];
    for(size_t j=0;j<face.mNumIndices; j++)
    {
      indicez.push_back(face.mIndices[j]);
    }
  }

  mesh new_mesh;
  new_mesh.create_mesh_via_assimp(verticez,indicez);

  new_mesh.set_light_bool(true);
  M_Model_Flag mm_flag= M_Model_Flag::MODEL_UNIFORM|M_Model_Flag::MODEL_HAS_NORM;

  //MODEL_USE_INDIC = 0x20,
  new_mesh.set_model_flag(mm_flag);
  std::cout << "newmeshadded_tomodel\n";

  glm::vec3 shipA2_emis            =glm::vec3(0.0f);
  glm::vec3 shipA2_amb_ref         =glm::vec3(0.5,0.6,0.8);
  glm::vec3 shipA2_diff_ref        =glm::vec3(0.5,0.5,0.5);
  glm::vec3 shipA2_spektral_reflect=glm::vec3(1.0,1.0,1.0);
  float     shipA2_shinyz          =600;

  new_mesh.set_meterial(shipA2_emis,shipA2_amb_ref,shipA2_diff_ref,
                        shipA2_spektral_reflect,shipA2_shinyz);
  return new_mesh;


}



};
