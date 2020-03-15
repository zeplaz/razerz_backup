

#include <stddef.h>
#include "geometry.hpp"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb_image.h"


std::ostream& operator << (std::ostream &out, const M_Tex_Flag &f)
{
     unsigned char  flag;
    flag  =(unsigned char) f;
    out << flag <<'\n';
    return out;
}

GLenum Texture_gl::return_TextureFormat(Format formate)
{
  switch (formate)
   {
      case Format::Format_Grayscale: return GL_LUMINANCE;
      case Format::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
      case Format::Format_RGB: return GL_RGB;
      case Format::Format_RGBA: return GL_RGBA;
      case Format::Format_RGBA8: return GL_RGBA8;
      case Format::Format_RGB8: return GL_RGB8;
      default: throw std::runtime_error("Unrecognised Bitmap::Format");
  }
}

  void mesh::pack_mesh_vertex(std::vector<glm::vec3>&in_v,std::vector< glm::vec3>&in_n,
                        std::vector< glm::vec2>&in_tc)
  {
    for(size_t i = 0; i<in_v.size(); i++ )
    {
      mesh_vertex temp_mv;
      temp_mv.v_position = in_v[i];
      temp_mv.v_normal = in_n[i];
      temp_mv.v_textcord = in_tc[i];
      m_vertices->push_back(temp_mv);
    }
  }
  void mesh::pass_meterial_data(gl_shader_t* shader)
  {
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.emission")        ,1,glm::value_ptr(meterial.emission));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.ambient_reflect") ,1,glm::value_ptr(meterial.ambient_reflect));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.diffuse_reflect") ,1,glm::value_ptr(meterial.diffuse_reflect));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.specular_reflect"),1,glm::value_ptr(meterial.specular_reflect));
    glUniform1f (glGetUniformLocation(shader->program_ID,"meterial.shininess")       ,meterial.shininess);
    glUniform1i (glGetUniformLocation(shader->program_ID,"meterial.is_normalmap")    ,meterial.is_normalmap);
  }

  void mesh::draw(gl_shader_t* shader,view_lenz* active_lenz)
  {
    shader->use_shader();
    glBindVertexArray(VAO_mesh);

    glm::mat4 active_projection(1.f);
    glm::mat4 active_view(1.f);
    active_projection = active_lenz->lenz_projection();
    active_view       = active_lenz->return_lenz_view();

    glm::mat4 view_projection(1.f);
    view_projection = active_projection*active_view;
    m_v_p = glm::mat4(1.f);
    m_v_p = view_projection*base_model_matrix;
    pass_meterial_data(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
    //glUniformMatrix4fv(shader->return_uniform("model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
    // texture drawing
    if(tex_flagz == M_Tex_Flag::TEXTYR_BASIC)
    { //std::cout <<"only basic texutre" << '\n';
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }
      //std::cout<<"number of veriz to draw::" << m_vertices->size() << '\n';
      glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());
  }

///////////////////////////////////////////////////
void mesh::draw_element(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj)
{
  shader->use_shader();
  glBindVertexArray(VAO_mesh);

  glm::mat4 proj_view(1.f);
  //model drawing
  if(cal_lightz == true)
  {
     glm::mat4 model_view(1.f);
     glm::mat3 normal_matrix(1.f);
     m_v_p = glm::mat4(1.f);

     model_view = view*base_model_matrix;
    //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
    normal_matrix = glm::inverse(glm::mat3(model_view));

    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
    glUniformMatrix3fv(shader->return_uniform("normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
    glUniformMatrix4fv(shader->return_uniform("model_view"),1,GL_FALSE,glm::value_ptr(model_view));
    glUniformMatrix4fv(shader->return_uniform("model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

    pass_meterial_data(shader);
  }

  else
  {
    m_v_p = glm::mat4(1.f);
    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
  }

  // texture drawing
  if(tex_flagz == M_Tex_Flag::TEXTYR_BASIC)
  { //std::cout <<"only basic texutre" << '\n';
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
          == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
          == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
          == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  glDrawElements(GL_TRIANGLES, m_v_indices->size(),GL_UNSIGNED_INT,0);
  glBindVertexArray(0);

}
/////////////////////////////////////
  void mesh::draw(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj)
  {
    shader->use_shader();
    glBindVertexArray(VAO_mesh);

    glm::mat4 proj_view(1.f);
    //model drawing
    if(cal_lightz == true)
    {
       glm::mat4 model_view(1.f);
       glm::mat3 normal_matrix(1.f);
       m_v_p = glm::mat4(1.f);

       model_view = view*base_model_matrix;
      //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
      normal_matrix = glm::inverse(glm::mat3(model_view));

      proj_view = proj*view;

      m_v_p = proj_view*base_model_matrix;
      glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
      glUniformMatrix3fv(shader->return_uniform("normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
      glUniformMatrix4fv(shader->return_uniform("model_view"),1,GL_FALSE,glm::value_ptr(model_view));
      glUniformMatrix4fv(shader->return_uniform("model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

      pass_meterial_data(shader);
    }

    else
    {
      m_v_p = glm::mat4(1.f);
      proj_view = proj*view;

      m_v_p = proj_view*base_model_matrix;
      glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
    }

    // texture drawing
    if(tex_flagz == M_Tex_Flag::TEXTYR_BASIC)
    { //std::cout <<"only basic texutre" << '\n';
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());

  }

  void mesh::draw(gl_shader_t* shader)
  {
    shader->use_shader();
    glBindVertexArray(VAO_mesh);

    //model drawing
    if(Model_flagz==M_Model_Flag::MODEL_UNIFORM)
    {
      glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_matrix"),
                                  1,GL_FALSE,glm::value_ptr(base_model_matrix));
    }

    // texture drawing
    if(tex_flagz == M_Tex_Flag::TEXTYR_BASIC)
    { //std::cout <<"only basic texutre" << '\n';
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[1].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());
    //glBindVertexArray(0);
  }


void mesh::pack_mesh_vertex(parsed_paket_type* par_pak)
{
  mesh_vertex temp_mv;
  for(size_t i = 0; i<par_pak->vertices.size(); i++ )
  {
    temp_mv.v_position   =par_pak->vertices[i];
    temp_mv.v_normal     =par_pak->normals[i];
    temp_mv.v_textcord   =par_pak->uvs[i] ;
    m_vertices->push_back(temp_mv);
  }
}

  void mesh::model_init()
  {
    base_model_matrix = glm::mat4(1.0f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);
  }

  void mesh::update_mesh_model(model_ajustment ajust_in)
  {
   rotation_base.x +=ajust_in.rotation_ajust.x;
    rotation_base.y +=ajust_in.rotation_ajust.y;
    rotation_base.z +=ajust_in.rotation_ajust.z;
    posz_base.x     +=ajust_in.posz_ajust.x;
    posz_base.y     +=ajust_in.posz_ajust.y;
    posz_base.z     +=ajust_in.posz_ajust.z;
    scale_base.x    +=ajust_in.scale_ajust.x;
    scale_base.y    +=ajust_in.scale_ajust.y;
    scale_base.z    +=ajust_in.scale_ajust.z;

    base_model_matrix = glm::mat4(1.f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);

  }

  void mesh::set_mesh_model_origin(model_ajustment intial_model)
  {
    rotation_base.x =intial_model.rotation_ajust.x;
    rotation_base.y =intial_model.rotation_ajust.y;
    rotation_base.z =intial_model.rotation_ajust.z;
    posz_base.x     =intial_model.posz_ajust.x;
    posz_base.y     =intial_model.posz_ajust.y;
    posz_base.z     =intial_model.posz_ajust.z;
    scale_base.x    =intial_model.scale_ajust.x;
    scale_base.y    =intial_model.scale_ajust.y;
    scale_base.z    =intial_model.scale_ajust.z;

    base_model_matrix =glm::mat4(1.f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);
  }

  void mesh::buff_setup_viaAssimp()
  {
    glGenVertexArrays(1,&VAO_mesh);
    glGenBuffers(1,&buff_mesh);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO_mesh);
    glBindBuffer(GL_ARRAY_BUFFER,buff_mesh);

    glBufferData(GL_ARRAY_BUFFER,m_vertices->size()*sizeof(mesh_vertex),&m_vertices->front(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_v_indices->size()*sizeof(unsigned int), &m_v_indices->front(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_textcord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_bitagent));

    glBindVertexArray(0);
  }

  void mesh::bindmesh_buf()
  {
    glGenVertexArrays(1, &VAO_mesh);
    glBindVertexArray(VAO_mesh);

    glGenBuffers(1,&buff_mesh);

    glBindBuffer(GL_ARRAY_BUFFER, buff_mesh);

    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_vertex)*m_vertices->size(),
                 &m_vertices->front(),GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex), 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex),BUFFER_OFFSET(sizeof(glm::vec3)));
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex),BUFFER_OFFSET(sizeof(glm::vec3)+sizeof(glm::vec3)));
   glEnableVertexAttribArray(2);

   glBindVertexArray(0);
   //std::vector<mesh_vertex> meshv = *m_vertices;
   /*
   std::cout << "size of meshvertz" << m_vertices->size() <<'\n';
   for(size_t i = 0; i<m_vertices->size(); i++)
   {
     std::cout << "vdata::" << m_vertices->at(i) <<'\n';
   }
   std::cout << "enddata \n \n";
   std::vector<glm::vec3> pos_vec;
   std::vector<glm::vec3> vnormz;
   std::vector<glm::vec2> tex_vec;

     for(size_t i = 0; i<m_vertices->size(); i++)
     {   mesh_vertex* mv_ptr = & m_vertices->at(i);
         pos_vec.push_back(mv_ptr->v_position);
         vnormz.push_back(mv_ptr->v_normal);
         tex_vec.push_back(mv_ptr->v_textcord);
     }*/
 /*
 glBufferSubData(GL_ARRAY_BUFFER,0,m_vertices->size() * sizeof(glm::vec3),&pos_vec.front());
 glBufferSubData(GL_ARRAY_BUFFER,m_vertices->size() * sizeof(glm::vec3)
     ,m_vertices->size() * sizeof(glm::vec3),&vnormz.front());

 glBufferSubData(GL_ARRAY_BUFFER,m_vertices->size() * sizeof(glm::vec3)+m_vertices->size() * sizeof(glm::vec3)
     ,m_vertices->size() * sizeof(glm::vec2),&tex_vec.front());*/
  }

    void Texture_gl::init_texture()
    {
      glActiveTexture(GL_TEXTURE0+texture_indexUnit);
      glBindTexture(GL_TEXTURE_2D,texture_ID);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexImage2D(GL_TEXTURE_2D, 0, return_TextureFormat(formate_internal), width, height, 0, return_TextureFormat(formate_external), GL_UNSIGNED_BYTE, image);
      stbi_image_free(image);
      glBindTexture(GL_TEXTURE_2D,0);
    }

    void Texture_gl::load_texture(std::string path,int force_channel,int text_unitindex)
    {
      std::cout <<"stbi_begin\n";
      image = stbi_load(path.c_str(),&width,&height,&n,force_channel);
      std::cout <<"stbi_loadcompleate\n";
      set_texture_unit_index(text_unitindex);
    }

    void Texture_gl::set_min_Mag_Filter(Filter filt,char min_mag)
      {
        switch (filt)
        {
          case Filter::LINEAR :
          {
           if(min_mag == 'i')
           minFiler = GL_LINEAR;
           if(min_mag == 'a')
           magFiler = GL_LINEAR;
           break;
          }
          case Filter::NEAREST :
          {
            if(min_mag == 'i')
            minFiler = GL_NEAREST;
            if(min_mag == 'a')
            magFiler = GL_NEAREST;
            break;
          }
          case Filter::MIPMAP :
          {
            if(min_mag == 'i')
            minFiler = GL_MIPMAP;
            if(min_mag == 'a')
            magFiler = GL_MIPMAP;
            break;
          }

          default : throw std::runtime_error("Unrecognised Bitmap::Filter");
        }
      }

      void calc_tanget_space(glm::vec3 pos, glm::vec3& tangent,glm::vec3& bytanget)
      {
        glm::vec3 edge1= pos;
      }

      void mesh::texture_setup(texture_paramz_pak in_text_pak)
      {
        std::cout << "##begin_textureLoad \n";

        Texture_gl new_texture;
        set_tex_flags(in_text_pak.text_type_flag);
        new_texture.set_texture_ST(in_text_pak.wm_s,'s');
        new_texture.set_texture_ST(in_text_pak.wm_t,'t');
        new_texture.set_min_Mag_Filter(in_text_pak.mag,'i');
        new_texture.set_min_Mag_Filter(in_text_pak.min,'a');

        new_texture.load_texture(in_text_pak.path,in_text_pak.channels,in_text_pak.tex_unit_index);
          std::cout << "##loadtexture_compleate \n";
        new_texture.init_texture();
          std::cout << "##init texture \n";
      //  new_texture.load_texture(in_text_pak.path);
        new_texture.set_Tex_paramz();
        std::cout << "##set_Tex pramz finished \n \n";
        if(in_text_pak.text_type_flag ==M_Tex_Flag::TEXTYR_BASIC)
        {
          m_texture_array[0]    = new_texture;
          m_tex_uniform_array[0]= in_text_pak.unform_name;
        }
        else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_NORMAL)
        {
          m_texture_array[1]      = new_texture;
          m_tex_uniform_array[1]  =in_text_pak.unform_name;
          meterial.is_normalmap = true;
        }
        else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_SPEKTURAL)
        {
          m_texture_array[2]    = new_texture;
          m_tex_uniform_array[2]=  in_text_pak.unform_name;
        }
      }


    /*
    void mesh::init(wavefornt_parser2* wp, std::string res_path)
    {
      std::pair<std::vector<vertex_type>*,
              std::vector<unsigned int>*> pars_vertex_data;
       pars_vertex_data= wp->read_file(res_path);
       m_vertices = pars_vertex_data.first;
       m_v_indices = pars_vertex_data.second;
      std::vector< glm::vec3 > vertices;
      std::vector< glm::vec3 > normals;
      std::vector< glm::vec2 > uvs;

      //wp->return_data(vertices,uvs,normals);
      //wp->gen_parse_parket(pars_pak_ptr);
      //pack_mesh_vertex(vertices,normals,uvs);


      posz_base    =glm::vec3(0.f);
      rotation_base=glm::vec3(0.f);
      scale_base   =glm::vec3(0.2f);
      //base_model_matrix = glm::mat4(1.0f);
      model_init();
    }*/
