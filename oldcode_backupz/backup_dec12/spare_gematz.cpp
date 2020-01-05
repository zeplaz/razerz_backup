
//from colour.hpp













void mesh::setup_mesh_4buf()
{
  glGenVertexArrays(1,&VAO_mesh);

  glGenBuffers(1,&vertex_buf);
  glGenBuffers(1,&uv_buf);
  glGenBuffers(1,&normal_buf);
  glGenBuffers(1,&element_buf);

  glBindVertexArray(VAO_mesh);

  glBindBuffer(GL_ARRAY_BUFFER,vertex_buf);
  glBufferData(GL_ARRAY_BUFFER,indexed_vertices.size()*sizeof(glm::vec3),
               &indexed_vertices[0],GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
  0,                  // attribute
  3,                  // size
  GL_FLOAT,           // type
  GL_FALSE,           // normalized?
  0,                  // stride
  (void*)0            // array buffer offset
);

  glBindBuffer(GL_ARRAY_BUFFER,uv_buf);
  glBufferData(GL_ARRAY_BUFFER,indexed_uvs.size()*sizeof(glm::vec2),
               &indexed_uvs[0],GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
  1,                                // attribute
  2,                                // size
  GL_FLOAT,                         // type
  GL_FALSE,                         // normalized?
  0,                                // stride
  (void*)0                          // array buffer offset
);

  glBindBuffer(GL_ARRAY_BUFFER,normal_buf);
  glBufferData(GL_ARRAY_BUFFER,indexed_normals.size()*sizeof(glm::vec3),
               &indexed_normals[0],GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
  2,                                // attribute
  3,                                // size
  GL_FLOAT,                         // type
  GL_FALSE,                         // normalized?
  0,                                // stride
  (void*)0                          // array buffer offset
);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,element_buf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices.size()*sizeof(unsigned int),
              &m_indices[0],GL_STATIC_DRAW);
}
/*mesh::mesh(std::vector<mesh_vertex>verticies)
    {
      this->m_vertices =verticies;
      //this->m_indices  =indices;
    //  this->m_textures =textures;
      inialize_indexer_VBO();
      setup_mesh_4buf();
    }

    mesh::mesh(std::vector<glm::vec3> in_position,
               std::vector<glm::vec3> in_normal,
               std::vector<glm::vec2> in_textcord)
        {
          //this->m_vertices =verticies;
        //  this->m_indices  =indices;
          //this->m_textures =textures;
          //inialize_indexer_VBO();
          index_VBO(in_position,in_textcord,in_normal,m_indices,
                    indexed_vertices,indexed_uvs,indexed_normals);
          setup_mesh_4buf();
        }*/


void update_mesh_model(glm::vec3 in_rotation, glm::vec3 in_movment,glm::vec3 in_scale)
{
  rotation_base.x +=in_rotation.x;
  rotation_base.y +=in_rotation.y;
  rotation_base.z +=in_rotation.z;
  posz_base.x     +=in_movment.x;
  posz_base.y     +=in_movment.y;
  posz_base.z     +=in_movment.z;
  scale_base.x    +=in_scale.x;
  scale_base.y    +=in_scale.y;
  scale_base.z    +=in_scale.z;

  base_model_matrix =glm::mat4(1.f);
  base_model_matrix = glm::translate(base_model_matrix, posz_base);
  base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
  base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
  base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
  base_model_matrix = glm::scale(base_model_matrix,scale_base);
}
bool get_sim_vertex_index(mesh_vertex& mv_pack, std::map<mesh_vertex,unsigned int>& vertex_outindex,
                          unsigned int &result);

void index_VBO_packed (std::vector<mesh_vertex> in_vec_vertex,
                std::vector<unsigned int> & out_indices,
                std::vector<glm::vec3> & out_vertices,
                std::vector<glm::vec2> & out_uvs,
                std::vector<glm::vec3> & out_normals);


void index_VBO(std::vector<glm::vec3> & in_vertices,
               std::vector<glm::vec2> & in_uvs,
               std::vector<glm::vec3> & in_normals,
               std::vector<unsigned int> & out_indices,
               std::vector<glm::vec3> & out_vertices,
               std::vector<glm::vec2> & out_uvs,
               std::vector<glm::vec3> & out_normals
);
void   mesh::setup_mesh_packed()
    {
      glGenVertexArrays(1,&VAO_mesh);
      glGenBuffers(1,&buff_mesh);
      glGenBuffers(1,&EBO);

      glBindVertexArray(VAO_mesh);

      glBindBuffer(GL_ARRAY_BUFFER,buff_mesh);

      glBufferData(GL_ARRAY_BUFFER,m_vertices.size()*sizeof(mesh_vertex),&m_vertices[0],GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices.size()*sizeof(unsigned int), &m_indices[0],GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)0);

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_normal));

      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_textcord));

      glBindVertexArray(0);

    }

    bool get_sim_vertex_index(mesh_vertex& mv_pack, std::map<mesh_vertex,unsigned int>& vertex_outindex,
                              unsigned int &result)
        {
          std::map<mesh_vertex,unsigned int>::iterator it = vertex_outindex.find(mv_pack);
          if(it ==vertex_outindex.end())
          {return false;}
          else
          {
            result= it->second;
            return true;
          }
        }
    void index_VBO_packed (std::vector<mesh_vertex> in_vec_vertex,
                	  std::vector<unsigned int> & out_indices,
                  	std::vector<glm::vec3> & out_vertices,
                  	std::vector<glm::vec2> & out_uvs,
                  	std::vector<glm::vec3> & out_normals
    )

    {
    std::map<mesh_vertex,unsigned int> vertex_outindex;
    for(unsigned int i =0; i<in_vec_vertex.size();i++)
    {

      mesh_vertex v_pack = in_vec_vertex[i];//{in_vertices[i], in_uvs[i], in_normals[i]};
      unsigned int index;
      bool found = get_sim_vertex_index(v_pack,vertex_outindex,index);
      if(found)
      {
        out_indices.push_back(index);
      } else
      {
          out_vertices.push_back( v_pack.v_position);
    			out_uvs     .push_back( v_pack.v_textcord);
    			out_normals
/*mesh::mesh(std::vector<mesh_vertex>verticies)
    {
      this->m_vertices =verticies;
      //this->m_indices  =indices;
    //  this->m_textures =textures;
      inialize_indexer_VBO();
      setup_mesh_4buf();
    }

    mesh::mesh(std::vector<glm::vec3> in_position,
               std::vector<glm::vec3> in_normal,
               std::vector<glm::vec2> in_textcord)
        {
          //this->m_vertices =verticies;
        //  this->m_indices  =indices;
          //this->m_textures =textures;
          //inialize_indexer_VBO();
          index_VBO(in_position,in_textcord,in_normal,m_indices,
                    indexed_vertices,indexed_uvs,indexed_normals);
          setup_mesh_4buf();
        }*/


    void mesh::setup_mesh_4buf()
    {
      glGenVertexArrays(1,&VAO_mesh);

      glGenBuffers(1,&vertex_buf);
      glGenBuffers(1,&uv_buf);
      glGenBuffers(1,&normal_buf);
      glGenBuffers(1,&element_buf);

      glBindVertexArray(VAO_mesh);

      glBindBuffer(GL_ARRAY_BUFFER,vertex_buf);
      glBufferData(GL_ARRAY_BUFFER,indexed_vertices.size()*sizeof(glm::vec3),
                   &indexed_vertices[0],GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

      glBindBuffer(GL_ARRAY_BUFFER,uv_buf);
      glBufferData(GL_ARRAY_BUFFER,indexed_uvs.size()*sizeof(glm::vec2),
                   &indexed_uvs[0],GL_STATIC_DRAW);

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,         .push_back( v_pack.v_normal);
    			unsigned int newindex = (unsigned int)out_vertices.size() - 1;
    			out_indices .push_back( newindex );
    			vertex_outindex[ v_pack ] = newindex;
      }
    }
    }

    void index_VBO(std::vector<glm::vec3> & in_vertices,
                   std::vector<glm::vec2> & in_uvs,
                   std::vector<glm::vec3> & in_normals,
                   std::vector<unsigned int> & out_indices,
                   std::vector<glm::vec3> & out_vertices,
                   std::vector<glm::vec2> & out_uvs,
                   std::vector<glm::vec3> & out_normals
    )

    {
    std::map<mesh_vertex,unsigned int> vertex_outindex;
    for(unsigned int i =0; i<in_vertices.size();i++)
    {

      mesh_vertex v_pack = {in_vertices[i],in_normals[i],in_uvs[i]};
      unsigned int index;
      bool found = get_sim_vertex_index(v_pack,vertex_outindex,index);
      if(found)
      {
        out_indices.push_back(index);
      } else
      {
          out_vertices.push_back( in_vertices[i]);
          out_uvs     .push_back( in_uvs[i]);
          out_normals .push_back( in_normals[i]);
          unsigned int newindex = (unsigned int)out_vertices.size() - 1;
          out_indices .push_back( newindex );
          vertex_outindex[ v_pack ] = newindex;
      }
    }
    }
