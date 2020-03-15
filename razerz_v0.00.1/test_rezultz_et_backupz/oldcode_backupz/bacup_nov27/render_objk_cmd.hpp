#pragma once

#include "gl_lib_z.hpp"

#include <tuple>
#include <map>
#include <list>
typedef std::tuple<unsigned char,int,int,int,GLfloat*,GLfloat*> f_sp_tuple;

#define GET_FET_FLAGZ 0
#define GET_FET_POS_SIZE 1
#define GET_FET_COLOUR_SIZE 2
#define GET_FET_NUMVERX 3
#define GET_FET_POS_DATA 4
#define GET_FET_COLOUR_DATA 5

//#define OBJK_STATE_ACTIVE 0x0002
//#define OBJK_STATE_CULL  0x0004


//constexpr unsigned char POLLY_ATTR_       {0b0000'1000};
//constexpr unsigned char POLLY_ATTR_       {0b0001'0000};

//constexpr unsigned char ATTRBUT_STREAM      {0b0000'1000};



typedef struct poly_3d_base_type
{
  unsigned char poly_STATE;
  unsigned char poly_attributez;

  glm::vec2 texture_cordz;
  glm::vec3 centriodxyz;
  //glm::vec4 colourRGBA;
  glm::mat3 verx_matrix_pos;
  GLfloat colourRGBA[12]
  {
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f
  };

  GLfloat tri_vertex[9] =
  {
    0.f,0.f,0.f,
    0.f,0.f,0.f,
    0.f,0.f,0.f
  };
  void setstate_flag(unsigned char flag_in)
  {
    poly_STATE |= flag_in;
  }
  void clear_state(){poly_STATE = NULL_FLAG;}

  void set_vertexz(GLfloat floa_array[9])
  {
    tri_vertex[0] =floa_array[0];
    tri_vertex[1] =floa_array[1];
    tri_vertex[2] =floa_array[2];
    tri_vertex[3] =floa_array[3];
    tri_vertex[4] =floa_array[4];
    tri_vertex[5] =floa_array[5];
    tri_vertex[6] =floa_array[6];
    tri_vertex[7] =floa_array[7];
    tri_vertex[8] =floa_array[8];
  }

  void set_vertexz(float x1,float y1,float z1, float x2, float y2, float z2,
                  float x3, float y3, float z3)
                  {
                    tri_vertex[0] =x1;
                    tri_vertex[1] =y1;
                    tri_vertex[2] =z1;
                    tri_vertex[3] =x2;
                    tri_vertex[4] =y2;
                    tri_vertex[5] =z2;
                    tri_vertex[6] =x3;
                    tri_vertex[7] =y3;
                    tri_vertex[8] =z3;
                  }
void set_colour_base(float r1, float g1,float b1,float a1,float r2,float g2, float b2,
                      float a2, float r3,float g3, float b3,float a3)

{
  colourRGBA[0] =r1;
  colourRGBA[1] =g1;
  colourRGBA[2] =b1;
  colourRGBA[3] =a1;
  colourRGBA[4] =r2;
  colourRGBA[5] =g2;
  colourRGBA[6] =b2;
  colourRGBA[7] =a2;
  colourRGBA[8] =r3;
  colourRGBA[9] =g3;
  colourRGBA[10]=b3;
  colourRGBA[11]=a3;
}

} tri_base_poly3d;

class objk_rendeable
{
  private :
  uint obj_gobal_ID;
  unsigned char obk_STATE={STATE_ACTIVE};
  unsigned char obj_attributez;
  int poly_count;

  std::vector<tri_base_poly3d> tri_ploy_list;

  public :
  void draw_to_gl();

  };

typedef struct render_list_type
{
  std::map<char,objk_rendeable*> objk_render_map;
  std::list<objk_rendeable> render_master_list;
} render_list;

class render_gl
{
  private :
  int num_obj_render_counter;

  public :
  render_list master_render_list;

};



class Basic_vertex_array_buffer

{
  private :
  unsigned int vertx_obj_ID;

  public :
  unsigned int v_buf_ID;
  unsigned int v_arry_O;
  ~Basic_vertex_array_buffer()
  {
    glDeleteBuffers(1,&v_buf_ID);
  }
void set_verx_via_pos_col(GLfloat* pos_f,GLfloat* col_f)
{
  glGenVertexArrays(1, &v_arry_O);
  glGenBuffers(1,&v_buf_ID);
  glBindVertexArray(v_arry_O);
  glBindBuffer(GL_ARRAY_BUFFER,v_buf_ID);
  int size_p = 9;//*(&pos_f + 1) - pos_f;
  int size_c = *(&col_f + 1) - col_f;
  std::cout << "poszie:" << size_p << " size_colarry::" << size_c <<'\n';
  //glBufferData(GL_ARRAY_BUFFER,size,data, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER,0,size_p*sizeof(float),&pos_f[0]);
  glBufferSubData(GL_ARRAY_BUFFER,size_p*sizeof(float),size_c*sizeof(float),&col_f[0]);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
  glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
}

void   set_Verx_buf(const void* data,int size)
{
  glGenBuffers(1,&v_buf_ID);
  glBindBuffer(GL_ARRAY_BUFFER,v_buf_ID);
  glBufferData(GL_ARRAY_BUFFER,size,data, GL_DYNAMIC_DRAW);
}
  void bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER,v_buf_ID);
  }
  void unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER,0);
  }
};

/*
class lightz_gl
{
  private :
  GLuint s_Program_ID;
  GLint ambientLightUinform_ID;
  GLint light_pos_uniform_ID;
  GLint lenz_pos_world_uniform_ID;

  glm::vec4 ambient_light_3Depth;
  glm::vec3 light_pos_world3Depth;
  public :

  void set_shader_program(GLuint p_id)
  {
    s_Program_ID = p_id;
  }
  void set_force_ambient_light(float r, float g, float b,float a)
  {
    ambient_light_3Depth[0]= r;
    ambient_light_3Depth[1]= g;
    ambient_light_3Depth[2]= b;
    ambient_light_3Depth[3]= a;
  }
  void cal_gl_uniformz(view_lenz& active_lenz, GLuint prog_ID)
  { prog_ID= s_Program_ID;
    ambientLightUinform_ID = glGetUniformLocation(prog_ID,"u_ambient_light");
    light_pos_uniform_ID = glGetUniformLocation(prog_ID,"u_light_pos_world");
    lenz_pos_world_uniform_ID = glGetUniformLocation(prog_ID,"u_lenz_pos_world");

    glm::vec3 lenz_pos_vec = active_lenz.get_position_glm();

    glUniform3fv(lenz_pos_world_uniform_ID,1,&lenz_pos_vec[0]);
    glUniform4fv(ambientLightUinform_ID,1,&ambient_light_3Depth[0]);
    glUniform3fv(light_pos_uniform_ID,1,&light_pos_world3Depth[0]);

  }
};*/
