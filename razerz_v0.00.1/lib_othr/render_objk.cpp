//render_objk.cpp
#include "render_objk_cmd.hpp"

auto get_buf_oset = [](f_sp_tuple& fetu_tup)
{
  return std::get<GET_FET_NUMVERX>(fetu_tup);
};


void draw_able_gl::settup_Vertex_array_Objeck(GLuint shader_pos,GLuint shader_colour,GLuint programID, int num_arrayz, GLuint* vao_array,
  f_sp_tuple& in_fetu_tuple, GLuint* buffer_in_array)
{

  glGenVertexArrays(num_arrayz,vao_array);

  for(size_t i = 0; i< sizeof(vao_array);i++)
  {
    glBindVertexArray(vao_array[i]);
    load_gl_buffer(buffer_in_array[i],in_fetu_tuple);
    glBindBuffer(GL_ARRAY_BUFFER,buffer_in_array[i]);

    glEnableVertexAttribArray(shader_pos);
    glEnableVertexAttribArray(shader_colour);

    glVertexAttribPointer(shader_pos,3,GL_FLOAT,GL_FALSE,0,0);
    glVertexAttribPointer(shader_colour,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET((get_buf_oset(in_fetu_tuple))*3*sizeof(GLfloat)));
    ptr_buffer_index_ID =buffer_in_array;
  //  index_Vr_buf_ob = *vao_array;
  }
}


void draw_able_gl::load_gl_buffer(GLuint& buffer, f_sp_tuple& in_feturez)
{
  bool continz = true;
  glGenBuffers(1,&buffer);
  glBindBuffer(GL_ARRAY_BUFFER,buffer);

//  std::get<GET_FET_POS_SIZE>(in_feturez)
  //std::get<GET_FET_COLOUR_SIZE>(in_feturez)
//  std::get<GET_FET_NUMVERX>(in_feturez)
//

  /*
  size_t pos_space = num_prtz*pos_depth*sizeof(GLfloat);
  size_t colour_space = num_prtz*colour_depth*sizeof(GLfloat);
  size_t feture_toal_space = pos_space+colour_space;
*/
size_t pos_space = std::get<GET_FET_NUMVERX>(in_feturez)*std::get<GET_FET_POS_SIZE>(in_feturez)*sizeof(GLfloat);
size_t colour_space = std::get<GET_FET_NUMVERX>(in_feturez)*std::get<GET_FET_COLOUR_SIZE>(in_feturez)*sizeof(GLfloat);
size_t feture_toal_space = pos_space+colour_space;

  switch(std::get<GET_FET_FLAGZ>(in_feturez))
  {
    case ATTRBUT_STATIC :
    glBufferData(GL_ARRAY_BUFFER,feture_toal_space, NULL, GL_STATIC_DRAW);

    break;

    case ATTRBUT_DYNAMIC_DRAW :
    glBufferData(GL_ARRAY_BUFFER, feture_toal_space, NULL, GL_DYNAMIC_DRAW);

    break;

    case ATTRBUT_STREAM :
    glBufferData(GL_ARRAY_BUFFER,feture_toal_space, NULL, GL_STREAM_DRAW);

    break;
    default :
    std::cout <<"no flag set for buffertype...orwhav no buf data set?\n";
    continz = false;
    break;
  }

  if(!continz)
  {
    glBufferSubData(GL_ARRAY_BUFFER,0,pos_space,std::get<GET_FET_POS_DATA>(in_feturez));
    glBufferSubData(GL_ARRAY_BUFFER,pos_space,colour_space,std::get<GET_FET_COLOUR_DATA>(in_feturez));
  }
}
