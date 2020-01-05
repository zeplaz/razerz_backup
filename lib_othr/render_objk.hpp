
#pragma once
#include "gl_lib_z.hpp"
#include <tuple>
typedef std::tuple<unsigned char,int,int,int,GLfloat*,GLfloat*> f_sp_tuple;

#define GET_FET_FLAGZ 0
#define GET_FET_POS_SIZE 1
#define GET_FET_COLOUR_SIZE 2
#define GET_FET_NUMVERX 3
#define GET_FET_POS_DATA 4
#define GET_FET_COLOUR_DATA 5

//#define OBJK_STATE_ACTIVE 0x0002
//#define OBJK_STATE_CULL  0x0004
constexpr unsigned char NULL_FLAG         {0b0000'0000};
constexpr unsigned char STATE_ACTIVE      {0b0000'0010};
constexpr unsigned char STATE_CULL        {0b0000'0100};

constexpr unsigned char POLLY_ATTR_       {0b0000'1000};
constexpr unsigned char POLLY_ATTR_       {0b0001'0000};

//constexpr unsigned char ATTRBUT_STREAM      {0b0000'1000};
#include <string_view>

constexpr std::string_view view_to_string = "";

constexpr auto SOMEDEFINE "string";
//also the string view
//c++20
constinit static std::mutex smutex;

std::coped_lock 1(mymutex);
constinit static auto vl =;

constexpr auto l=[](){};
//template<class d_type>

void add_depented(gui_handle gui_hand)
{
  .push_back(gui_hand)
}
template <typename T, typename... P>
 inline T *add_depented(P&&... p)
 {
         auto handle = Util::make_handle<T>(std::forward<P>(p)...);
         add_child(handle);
         return static_cast<T *>(handle.get());
 }


<iomanip>

//std::setprecision(std::numeric_limits<long double>::digits10+1);

template<Typename type>
constexpr auto func = [](const Type &ref,etc..)
{
  return ;
}

//clall
auto outvalue = func<int>( stuf...);

//stander array
template<typename typea, typename type2>
constexpr bool is_same = false;

template<typename typea>
constexpr bool is_same<T,T> = true;

std::pair<type1,type2> values{1,2};
auto[first,second]= values;
if(auto[first,second]= values;
    first /oprerator 4)
    {

    }
//


template<typename ... Type>
auto function(Const T& ... params)
{
  return (params /operator ...);
}


##include<cstring>
template<typename d_type,class in_type>
struct byte_updater
{

  d_type stuc_sotrage;

  void updateviamemcopy(char*blobofbyez,in_type in_data,int index)
  {
    memcopy(stuc_sotrage,blobofbyez,sizeof(stuc_sotrage));
    //preform update use in_data at index
    memcopy(blobofbyez,stuc_sotrage,sizeof(stuc_sotrage));
  }
  void updateviamemcopy(char*blobofbyez,in_type in_data)
  {
    memcopy(stuc_sotrage,blobofbyez,sizeof(stuc_sotrage));
    //preform update use in_data
    memcopy(blobofbyez,stuc_sotrage,sizeof(stuc_sotrage));
  }
/*
  void updateviamemcopy(char*blobofbyez, vec4 in_data4)
  {
    memcopy(stuc_sotrage,blobofbyez,sizeof(stuc_sotrage));
  }*/
};

class render_gl
{
  private :
  int num_obj_render_counter;

  public :
  render_list master_render_list;

};

typedef struct render_list_type
{
  std::map<char,objk_rendeable*> objk_render_map;
  std::list<objk_rendeable> render_master_list;
} render_list;



class metrealz_gl
{

};


typedef struct poly_3d_base_type
{
  uchar poly_STATE;
  uchar poly_attributez;

  glm::vec2 texture_cordz;
  glm::vec3 centriodxyz;
  glm::vec4 colourRGBA;
  glm::mat3 verx_matrix_pos;
  GLfloat tri_vertex[] =
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
  void set_vertex(GLfloat floa_array[9])
  {
    tri_vertex=floa_array;
  }

  void set_vertex(GLfloat floa_array[9])

  void set_vertex(float x1,float y1,float z1, float x2, float y2, float z2
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
void set_colour_base(float r, float g,float b,float a)
{
  colourRGBA.x =r;
  colourRGBA.y =g;
  colourRGBA.z =b;
  colourRGBA.w =a;
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

//#define EPSILON_E5(float)(1E-5)

typedef struct  plane_3d_type
{
  vector3_vala<float> p0;
  vector3_vala<float> normal;

  float compute_depth_plane(vector3_vala<float>* pt, plane_3d* plane)
  {
  //  float hs = plane->n('x')*(pt('x'))
    float hs =  plane->normal.coordinates[0]*(pt->coordinates[0] - plane->p0.coordinates[0])+
                plane->normal.coordinates[1]*(pt->coordinates[1] - plane->p0.coordinates[1])+
                plane->normal.coordinates[2]*(pt->coordinates[2] - plane->p0.coordinates[2]);

    return hs;
  }

int intersect_line3d_plane(parameter_line* pline,plane_3d* plane, float*t,vector3_vala<float>* pt )
  {
    float plane_dot_line = Dot_vec_3d(&pline->v,&plane->normal);
    if(fabs(plane_dot_line)<=EPSILON_E5)
    {

    }

  }

} plane_3d;

typedef struct parameter_line_type
  {
    vector3_vala<float> p0;
    vector3_vala<float> p1;
    vector3_vala<float> v;

}parameter_line;


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

  set_shader_program(GLuint p_id)
  {
    s_Program_ID = p_id;
  }
  set_force_ambient_light(float r, float g, float b,float a)
  {
    ambient_light_3Depth[0]= r;
    ambient_light_3Depth[1]= g;
    ambient_light_3Depth[2]= b;
    ambient_light_3Depth[3]= a;
  }
  cal_gl_uniformz(GLuint prog_ID = s_Program_ID,view_lenz& active_lenz)
  {
    ambientLightUinform_ID = glGetUniformLocation(prog_ID,"u_ambient_light");
    light_pos_uniform_ID = glGetUniformLocation(prog_ID,"u_light_pos_world");
    lenz_pos_world_uniform_ID = glGetUniformLocation(prog_ID,"u_lenz_pos_world");

    glm::vec3 lenz_pos_vec = active_lenz.get_position_glm();

    glUniform3fv(lenz_pos_world_uniform_ID,1,&lenz_pos_vec[0]);
    glUniform4fv(ambientLightUinform_ID,1,&ambient_light_3Depth[0]);
    glUniform3fv(light_pos_uniform_ID,1,&light_pos_world3Depth[0]);

  }
};

//shape factory -> make object
//glVertexAttrib3f etc... (location,,000)
send_multi_data_gl()
{
  objkdata = genrator
  GLsuzeiptr current_offset;
  glGenBuffers(1,&the_big_buff_ID);
  glBindBuffer(GL_ARRAY_BUFFER,the_big_buff_ID);
  glBufferData(GL_ARRAY_BUFFER,total_size_data,0,GL_DYNAMIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER,0,);

}

void draw_(gl_shader& in_shader, GLuint* in_buffer,int num_draw)
{
  glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glUseProgram(in_shader.program_ID);
  //glBindBufferRange(GL_SHADER_STORAGE_BUFFER, index_layout, in_buffer, 0, 128);
  //glBindBuffer(GL_ARRAY_BUFFER,*in_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*in_buffer);
  //glUniform4f(location?,r,0.3f,0.8f,1.0f);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES,num_draw,GL_UNSIGNED_INT,NULL);
}

class indexable_buffer
{
  private :

  GLuint index_obj_buffer;

  GLuint* ptr_indicate_data;
  GLuint num_points;
  GLuint byte_size;
  unsigned int Indeable_ojk_ID;

  public :
  inline GLuint
  void set_indeictable(const unsigned int* data_inicez, GLuint d_size)
  {
    byte_size = d_size;
    ptr_indicate_data = data_inicez;
  }

  void index_VAO_buf_gen()
  {
    std::cout << "indexbinding_VAO\n";
    glGenBuffers(1,&index_obj_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_obj_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,num_points*sizeof(GLuint),ptr_indicate_data[0],GL_DYNAMIC_DRAW);

  }

  void bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_obj_buffer);
  }

  void unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  }

};
class Basic_vertex_array_buffer

{
  private :
  unsigned int vertx_obj_ID;

  public :
  unsigned int v_buf_ID;

  ~Basic_vertex_array_buffer()
  {
    glDeleteBuffers(1,&v_buf_ID);
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

class Element_array_buffer
{
  private :

  public :
  unsigned int v_buf_ID;


  void set_element_v_buf(const void* data,int size)
{
  glGenBuffers(1,&v_buf_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,v_buf_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data ,GL_DYNAMIC_DRAW);
}
  void render_vertex_array(int num_vertx)
  {
    glDrawArrays(GL_TRIANGLE_FAN, 0,num_vertx);
  }
};

class vertex_array_objectcapble
{
  public :

};
  class draw_able_gl
  {
    private :
    GLuint* ptr_buffer_index_ID;
    int size;

    render_mode r_mode;

    public :

    void clear_bufferz(gl_shader& in_shader)
    {
      glUseProgram(in_shader.program_ID);
      glBindBuffer(GL_ARRAY_BUFFER,0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    void settup_Vertex_array_Objeck(GLuint shader_pos,GLuint shader_colour,GLuint programID, int num_arrayz, GLuint* vao_array,
      f_sp_tuple& in_fetu_tuple, GLuint* buffer_in_array);

      void gl_render_v3(view_lenz& in_lenz,gl_shader& in_shader)
      {
        if(r_mode ==render_mode::WIREFRAME)
        {
          glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }

        glBindVertexArray(*ptr_buffer_index_ID);

        in_lenz;

      }

    void render_elementz_indcatez()
    {

      if(r_mode ==render_mode::WIREFRAME)
      {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      }
      glBindVertexArray(*ptr_buffer_index_ID);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ptr_buffer_index_ID);
      glDrawElements(GL_TRIANGLES,size,GL_UNSIGNED_INT,NULL);
    }


    void load_gl_buffer(GLuint& buffer, f_sp_tuple& in_feturez);

    bool buffer_setup_ojkz(GLuint& vertex_bufz, GLuint& vertex_array_ojk, uint32_t positionAttributeIndex )
    {// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

      // Generate and assign two Vertex Buffer Objects to our handle
    	glGenBuffers(1, &vertex_bufz);
      glGenVertexArrays(1, &vertex_array_ojk);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_bufz);
      glBindVertexArray(vertex_array_ojk);
      //sizeof(MyVertex), BUFFER_OFFSET(0));
      //glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_array_ojk), BUFFER_OFFSET(0));
      //glEnableVertexAttribArray(positionAttributeIndex+1,4,GL_FLOAT,GL_FALSE,sizeof(verx_colour_obk),BUFFER_OFFSET(sizeof(float)*3));

      return true;
    }
    };

    class cube_gl
    {
      private:
        GLuint* cube_indices_data;
        GLfloat* cube_vertices_data;

      public :
      GLuint gl_vertices_vao_ID = 0;
      GLuint gl_indices_vao_ID = 0;
      unsigned char cube_flagz{0b0000'0101};
      //GLuint* vertex_array_ojk;

      void set_flagz(unsigned char flags)
      {
        cube_flagz |=flags;
      }

      void set_cube(GLuint* in_cube_indices, GLfloat* in_cube_vertices, unsigned char flags,int num_vertx)
      {
        set_flagz(flags);
        cube_indices_data  = in_cube_indices;
        cube_vertices_data = in_cube_vertices;
        glGenBuffers(1,&gl_vertices_vao_ID);
        glGenBuffers(1,&gl_indices_vao_ID);
        //select type of object...

        glBindBuffer(GL_ARRAY_BUFFER,gl_vertices_vao_ID);

        if(cube_flagz & ATTRBUT_DYNAMIC_DRAW)
        {
          glBufferData(GL_ARRAY_BUFFER,sizeof(cube_vertices_data),cube_vertices_data[0],GL_DYNAMIC_DRAW);
        }
        else
        {
          glBufferData(GL_ARRAY_BUFFER,sizeof(cube_vertices_data),cube_vertices_data[0],GL_STATIC_DRAW);
        }
        //glBindBuffer(GL_ARRAY_BUFFER,0);
        glEnableVertexAttribArray(gl_vertices_vao_ID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*(3*num_vertx), BUFFER_OFFSET(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*(4*num_vertx), BUFFER_OFFSET(sizeof(GLfloat)*3*num_vertx));

      }
    };

/*
GLuint* create_cube(GLuint* in_cube_indices, GLfloat* in_cube_vertices)
{



  return vertex_array_ojk;
}
*/
