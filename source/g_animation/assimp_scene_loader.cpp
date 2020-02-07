

/*
int bone_array_size = assimp_mesh->mNumVertices*WEIGHTS_PER_VERTEX;

std::vector<int> joint_ID_vec;
joint_ID_vec.resize(bone_array_size);
*/

void animated_mesh_loader::recursive_node_process(aiNode* node)
{
  ai_nodez.push_back(node);
  for(size_t i =0; i<node->mNumChildren; i++)
  {
    recursive_node_process(node->mChildren[i]);
  }
}

void animated_mesh_loader::anim_node_process()
{
  
}

std::vector<animated_mesh> animated_mesh_loader::get_meshes()
{
  return meshes;
}

animated_mesh_loader::~animated_mesh_loader()
{
  for(int i=0;i<meshes.size();i++)
  {
    delete meshes[i];
  }
}

void animated_mesh_loader::recursive_processing(aiNode* node, const aiScene* scene)
{
  for(int i=0;i<node->mNumMeshes;i++)
  {
    aiMesh* mesh =scene->mMeshes[node->mMeshes[i]];
    process_mesh(mesh,scene);
  }

  for(int i=0;i<node->mNumChildren;i++)
  {
    recursive_processing(node->mChildren[i],scene);
  }
}

void animated_mesh_loader::process_mesh(aiMesh* mesh const aiScene* scene)
{
  std::vector<am_vertex_data> v_data;
  std::vector<unsigned int> indices;
  std::vector<texture_data> texturez;

  aiColor4D ai_colour;
  aiMaterial* aimat =scene->mMaterials[mesh->mMaterialIndex];

  aiGetMaterialColor(aimat,AI_MATKEY_COLOR_DIFFUSE,&ai_colour);

  glm::vec3 defaultColor(ai_colour.r,ai_colour.g,ai_colour.b);

  int joint_array_size = mesh->mNumVertices*WEIGHTS_PER_VERTEX;
  std::vector<int> joint_idz;
  joint_idz.resize(joint_array_size);

  std::vector<float> joint_wieghtz;
  joint_wieghtz.resize(joint_array_size);

//construct vertexes

  for(int i=0;i<mesh->mNumVertices;i++)
	{
    am_vertex_data temp_verx;
    glm::vec3 temp_vec;
    glm::vec2 temp_2vec;
    temp_vec.x=mesh->mVertices[i].x;
		temp_vec.y=mesh->mVertices[i].y;
		temp_vec.z=mesh->mVertices[i].z;
    temp_verx.position =temp_vec;

    temp_vec.x=mesh->mNormals[i].x;
		temp_vec.y=mesh->mNormals[i].y;
		temp_vec.z=mesh->mNormals[i].z;
    temp_verx.normal=tmpVec;

    if(mesh->mTangents)
		{
      temp_vec.x=mesh->mTangents[i].x;
      temp_vec.y=mesh->mTangents[i].y;
      temp_vec.z=mesh->mTangents[i].z;
    }
    else{
      temp_vec.x=1.0;
      temp_vec.y=temp_vec.z=0;
    }
    temp_verx.tangent =temp_vec;

    if(mesh-mColors[0])
    {
      temp_vec.x=mesh->mColors[i].r;
      temp_vec.y=mesh->mColors[i].g;
      temp_vec.z=mesh->mColors[i].b;
    }
    else{temp_vec=defaultColor;}
    temp_verx.colour=temp_vec;

    if(mesh->mTextureCoords[0])
			{
        temp_2vec.x=mesh->mTextureCoords[0][i].x;
        temp_2vec.y=mesh->mTextureCoords[0][i].y;
      }
      else{
        temp_2vec = tmpVec.x=tmpVec.y=0.0;
      }
      temp_verx.uv =temp_2vec;
      v_data.push_back(temp_verx);
  }

//covnert joint and wieting and put in vertex data

    for(int i=0;i<mesh->mNumBones;i++)
    {
      aiBone* ai_joint mesh->mBones[i];
      for(int j=0;j<ai_joint->->mNumWeights;j++)
      {
        aiVertexWeight weight = ai_joint->mWeights[j];

        unsigned int vertex_start = wieght.mVertexID*WEIGHTS_PER_VERTEX;
        for(int k =0; k<WEIGHTS_PER_VERTEX;k++)
        {
          if(joint_wieghtz.at(vertex_start+k)==0)
          {
            vertex_start.at(vertex_start+k)= weight;
            joint_idz.at(vertex_start+k) =i;
            v_data.at(weight.mVertexId).weights[k] = weight.mWeight;
            break;
          }
        }
      }
    }

// add indicates
  for(int i=0;i<mesh->mNumFaces;i++)
  {
    aiFace face=mesh->mFaces[i];
    for(int j=0;j<face.mNumIndices;j++) //0..2
		{
			indices.push_back(face.mIndices[j]);
		}
  }

//texture stuff. FIX!
  for(int i=0;i<aimat->GetTextureCount(aiTextureType_DIFFUSE);i++)
  {
    aiString str;
    aimat->GetTexture(aiTextureType_DIFFUSE,i,&str);
    textureData tmptex;
    tmptex.id =
    tmptex.type = M_Tex_Flag::TEXTYR_DEFFUSE;

  }

  meshes.push_back(new animated_mesh::animated_mesh(v_data,indices,texturez));

}
