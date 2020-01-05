#pragma once

#include "gl_lib_z.hpp"
#include "shader_parser.hpp"
#include "geometry_parser.hpp"

class wavefornt_parser2;



typedef struct model_ajustment_type
{
  glm::vec3 posz_ajust;
  glm::vec3 rotation_ajust;
  glm::vec3 scale_ajust;
}model_ajustment;

struct texture_paramz_pak
{
  WarpMode wm_s;
  WarpMode wm_t;
  Filter mag;
  Filter min;
  std::string path;
  int channels;
  std::string unform_name;
  M_Tex_Flag text_type_flag;
  int tex_unit_index;
};

 struct Texture_gl
    {
        GLuint texture_ID;
        int texture_indexUnit = 0;
        unsigned char* image;

        int width, height,n;

        GLint minFiler = GL_LINEAR;
        GLint magFiler = GL_LINEAR;
        GLint wrapMode_S = GL_CLAMP_TO_EDGE;
        GLint wrapMode_T = GL_CLAMP_TO_EDGE;

        Format formate_internal;
        Format formate_external;


        GLenum return_TextureFormat(Format formate)
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

        Texture_gl()
        {
          formate_external =  Format::Format_RGB;
          formate_internal =  Format::Format_RGB8;
          glGenTextures(1,&texture_ID);
        }

        void activate()
        {
          glActiveTexture(GL_TEXTURE0+texture_indexUnit);
        }

        void set_texture_sampler_uniform(gl_shader_t* s_in,std::string uniform_name)
        {
          glBindTexture(GL_TEXTURE_2D,texture_ID);
          glUniform1i(glGetUniformLocation(s_in->program_ID, uniform_name.c_str()), 0);
        }

        void set_Tex_paramz()
        {
          activate();
          glBindTexture(GL_TEXTURE_2D,texture_ID);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFiler);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFiler);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode_S); //GL_REPEAT//GL_CLAMP_TO_EDGE//GL_CLAMP_TO_BORDER//GL_MIRRORED_REPEAT
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode_T);
        }
        void init_texture();

        void  set_texture_unit_index(int index)
        {
          texture_indexUnit +=index;
        }

        void load_texture(std::string path,int force_channel,int text_unitindex);

        void set_texture_ST(WarpMode mode, char st)
        {
          if(st =='t')
          {
            wrapMode_T =mode;
          }
          else{
            wrapMode_S =mode;
          }
        }
        void set_min_Mag_Filter(Filter filt,char min_mag);

};

typedef struct parsed_paket_type;
typedef struct vertex_type;



class mesh
{
  private :
  glm::vec3 posz_base;
  glm::vec3 rotation_base;
  glm::vec3 scale_base;
  glm::mat4 base_model_matrix;

  unsigned int VAO_mesh, buff_mesh, EBO;
  unsigned int vertex_buf, uv_buf, normal_buf,element_buf;
  std::string res_path;

  M_Tex_Flag tex_flagz     = M_Tex_Flag::TEXTYR_NULL;
  M_Model_Flag Model_flagz = M_Model_Flag::MODEL_NULL;

  public :
/*
  template<typename... Args>
   void flag_ORer(Args &&... flag_pack)//static
  {
       //unsigned char arg_array[]=  {((void) flag_ORer(std::forward<Args>(flag_pack)), ...)};
      int dummyflag_array[] = { ( (void) set_tex_flags(std::forward<Args>(flag_pack)),0) ... };
       std::cout <<  "size of dummy araybytz" << sizeof(dummyflag_array) <<'\n';
       std::cout <<  "data of dummy araybytz" << dummyflag_array[0] <<'\n';
  }*/


  std::vector<vertex_type>* m_vertices;
  std::vector<unsigned int>* m_v_indices;
  std::array<Texture_gl,3> m_texture_array;
  std::array<std::string,3> m_tex_uniform_array;
  //std::vector<std::pair<Texture_gl,std::string>> m_textures;

  ~mesh();

  void set_tex_flags(M_Tex_Flag t_flag)
  {
    std::cout <<"flagsetter texture set::" << (int)t_flag <<'\n';
    tex_flagz  |=t_flag;
    std::cout << "current texture flagz::" << (int)tex_flagz <<'\n';
  }

  void init(wavefornt_parser2* wp, std::string res_path);
  void init(std::pair<std::vector<vertex_type>*,std::vector<unsigned int>*> in_vertx_data,M_Model_Flag mm_flag)
  {
    m_vertices =in_vertx_data.first;
    m_v_indices = in_vertx_data.second;
    Model_flagz |=mm_flag;
    posz_base    =glm::vec3(0.f);
    rotation_base=glm::vec3(0.f);
    scale_base   =glm::vec3(0.2f);

    model_init();
  }
  void model_init();

  void texture_setup(texture_paramz_pak in_text_pak)
  {
    Texture_gl new_texture;
    set_tex_flags(in_text_pak.text_type_flag);
    new_texture.set_texture_ST(in_text_pak.wm_s,'s');
    new_texture.set_texture_ST(in_text_pak.wm_t,'t');
    new_texture.set_min_Mag_Filter(in_text_pak.mag,'i');
    new_texture.set_min_Mag_Filter(in_text_pak.min,'a');
    new_texture.load_texture(in_text_pak.path,in_text_pak.channels,in_text_pak.tex_unit_index);
    new_texture.init_texture();
    new_texture.set_Tex_paramz();
    if(in_text_pak.text_type_flag ==M_Tex_Flag::TEXTYR_BASIC)
    {
      m_texture_array[0]    = new_texture;
      m_tex_uniform_array[0]= in_text_pak.unform_name;
    }
    else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_NORMAL)
    {
      m_texture_array[1]      = new_texture;
      m_tex_uniform_array[1]=in_text_pak.unform_name;
    }
    else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_SPEKTURAL)
    {
      m_texture_array[2]    = new_texture;
      m_tex_uniform_array[2]=  in_text_pak.unform_name;
    }
  //  m_textures.push_back(std::make_pair(new_texture,in_text_pak.unform_name));
  }

  void pack_mesh_vertex(parsed_paket_type* par_pak);


  void pack_mesh_vertex(std::vector<glm::vec3>&in_v,std::vector< glm::vec3>&in_n,
                        std::vector< glm::vec2>&in_tc);

  void bindmesh_buf();

  void draw(gl_shader_t* shader)
  {
    shader->use_shader();

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
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0]);

    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0]);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1]);
    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0]);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1]);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[1]);
    }

    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
            == (M_Tex_Flag::TEXTYR_BASIC|M_Tex_Flag::TEXTYR_SPEKTURAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0]);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[1]);
    }
    /*for(size_t i=0; i<m_textures.size();i++)
    {
      std::pair<Texture_gl,std::string>* text_ptr  = &m_textures[i];
      text_ptr->first.activate();
      text_ptr->first.set_texture_sampler_uniform(shader,text_ptr->second);
    }*/
    glBindVertexArray(VAO_mesh);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());
    glBindVertexArray(0);
  }

  unsigned int return_elment_buf()
  {
    return element_buf;
  }

  size_t return_num_indices()
  {
    return m_v_indices->size();
  }

  void set_render_mode(render_mode new_mode, Poly_face face)
  {

       if(new_mode==render_mode::WIREFRAME)
         glPolygonMode(face,GL_LINE);

       if(new_mode==render_mode::FILL)
         glPolygonMode(face,GL_FILL);

       if(new_mode==render_mode::POINT)
        glPolygonMode(face,GL_POINT);
  }

  void update_mesh_model(model_ajustment ajust_in)
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

  void set_mesh_model_origin(model_ajustment intial_model)
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

};


class gl_lightz
{
  public :
  glm::vec3 light_pos;
  glm::vec3 light_colour;

  void set_light(glm::vec3 lp, glm::vec3 lc)
  {
    this->light_pos    =lp;
    this->light_colour =lc;
  }
};
