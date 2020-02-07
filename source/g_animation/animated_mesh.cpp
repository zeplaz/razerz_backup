
#include "animated_mesh.hpp"


animated_mesh::~animated_mesh()
{
  glDeleteBuffers(1,&am_VAO);
	glDeleteBuffers(1,&am_VBO);
  glDeleteBuffers(1,&am_IND);
}

void animated_mesh::set_attrabute_locations(unsigned int prog_ID)
{
  attrb_loc[0]=glGetAttribLocation(prog_ID,"position");
  attrb_loc[1]=glGetAttribLocation(prog_ID,"normal");
  attrb_loc[2]=glGetAttribLocation(prog_ID,"uv");
  attrb_loc[3]=glGetAttribLocation(prog_ID,"tangent");
  attrb_loc[4]=glGetAttribLocation(prog_ID,"colour");
  attrb_loc[5]=glGetAttribLocation(prog_ID,"jointIDs");
  attrb_loc[6]=glGetAttribLocation(prog_ID,"weights");

  attrb_loc[7]=glGetAttribLocation(prog_ID,"meterialID");

  joint_uniform_loc = glGetUniformLocation(prog_ID, "u_jonts");

}


void animated_mesh::draw(gl_shader_t* shader)
{
  shader->use_shader();
  glBindVertexArray(am_VAO);
  glUniformMatrix4fv(joint_uniform_loc,joint_matrixz.size(),GL_FALSE,glm::value_ptr(joint_matrixz[0]));


  glDrawElements(GL_TRIANGLES, indices->size(),GL_UNSIGNED_INT,0);
  //glDrawArrays(GL_TRIANGLES, 0, vertex_data->size());
  glBindVertexArray(0);
}

animated_mesh::animated_mesh(std::vector<am_vertex_data>&& vd, std::vector<unsigned int>&& indic,std::vector<texture_data>&& texdat = NULL)
{
  vertex_data = std::move(vd);
  indices   = std::move(indic);
  if(texdat!=NULL)
  {
    textures = std::move(texdat);
  }
}


void animated_mesh::buff_setup()
{

  glCreateVertexArrays(1,&am_VAO);
  glCreateBuffer(1,&am_VBO);

  glNamedBufferStorage(am_VBO,sizeof(vertex_data),vertex_data.first(),0);
  glVertexArrayBuffer(am_VAO,VERTEX_BINDING,am_VBO,0,sizeof(am_vertex_data));

  glVertexAttribFormat(attrb_loc[0],4,GL_float,GL_FALSE,offsetof(am_vertex_data,position));
  glVertexAttribFormat(attrb_loc[1],3,GL_float,GL_FALSE,offsetof(am_vertex_data,normal));
  glVertexAttribFormat(attrb_loc[2],2,GL_float,GL_FALSE,offsetof(am_vertex_data,uv));
  glVertexAttribFormat(attrb_loc[3],3,GL_float,GL_FALSE,offsetof(am_vertex_data,tangent));
  glVertexAttribFormat(attrb_loc[4],4,GL_float,GL_FALSE,offsetof(am_vertex_data,colour));
  glVertexAttribFormat(attrb_loc[5],4,GL_float,GL_FALSE,offsetof(am_vertex_data,jointIDs));
  glVertexAttribFormat(attrb_loc[6],4,GL_float,GL_FALSE,offsetof(am_vertex_data,weights));
  glVertexAttribIFormat(attrb_loc[7],GL_short,GL_FALSE,offsetof(am_vertex_data,meterialID));

  glVertexArrayAttibBinding(am_VAO,attrb_loc[0],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[1],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[2],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[3],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[4],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[5],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[6],VERTEX_BINDING);
  glVertexArrayAttibBinding(am_VAO,attrb_loc[7],VERTEX_BINDING);

  glEnableVertexArrayAttrib(attrb_loc[0]);
  glEnableVertexArrayAttrib(attrb_loc[1]);
  glEnableVertexArrayAttrib(attrb_loc[2]);
  glEnableVertexArrayAttrib(attrb_loc[3]);
  glEnableVertexArrayAttrib(attrb_loc[4]);
  glEnableVertexArrayAttrib(attrb_loc[5]);
  glEnableVertexArrayAttrib(attrb_loc[6]);
  glEnableVertexArrayAttrib(attrb_loc[7]);

  glGenBuffers(1,&am_IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,am_IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
}
