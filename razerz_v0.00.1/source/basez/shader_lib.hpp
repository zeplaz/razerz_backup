
#include "../sym_object.hpp"
#include "../gl_lib_z.hpp"

class shader_base :  public sym_object
{
  protected :
  bool use_pipe;
};

class shader_seprate : public shader_base
  {
    protected :

    public :
  void set_use_pipe()
    {
      use_pipe = true;
    }
};

class gl_shader_t
{
  private :
  shader_type contained_shaders=shader_type::SHADER_NULL;
  unsigned char shader_flags;
  std::map<int,std::pair<shader_type,std::string>> shader_code_map;
  std::map<int,std::pair<shader_type,GLuint>> shader_IDz_map;

  public :
  GLuint program_ID = 0;
  int Global_shader_ID = 0;
  std::unordered_map<std::string,GLuint> uniform_loc_map;

  bool create_link_program(std::vector<int>& to_attach_shaders);
  void create_shader(shader_type shad_type, int s_index);
  void setup_shader_code(shader_tuple_type* in_shader_tuple);
  void load_complie(int map_index);
  GLuint return_uniform(std::string name);

  shader_type get_contaned_shdertypes()
  {
    return contained_shaders;
  }

  inline void use_shader()
  {
    glUseProgram(program_ID);
  }

  inline void shutdown()
  {
    glDeleteShader(program_ID);
  }
  inline void set_glm_mat4(const std::string &name,const glm::mat4 &mat) const
  {
     glUniformMatrix4fv(glGetUniformLocation(program_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  inline void add_uniform(std::string name,GLuint uniform_loc)
  {
    uniform_loc_map.insert(std::make_pair(name,uniform_loc));
  }

   inline void test_flags()
  {
    //contained_shaders = shader_type::VERTEX_SHADER;
    std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders |= shader_type::FRAGMENT_SHADER;
    //std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders =contained_shaders& ~shader_type::VERTEX_SHADER;
    //  std::cout << "contaned flags:" << (int)contained_shaders;
    std::cout <<"\n \n";
  }

};

class shader_default : public shader_base
{
  protected :
  std::shared_ptr<gl_shader_t>  gl_def_shd;

  public :

  inline void set_use_pipe()
  { use_pipe = false; }

  void gen_glshd_def()
  {
      std::shared_ptr<gl_shader_t> temp_ptr (new gl_shader_t);
  }

  std::pair<,std::shared_ptr<gl_shader_t>> return_data_pair()
  {
    return std::make_pair(get_id(),gl_def_shd);
  }
};

/*
  template<class...Ts>
  void add_shaders_to_pipeline(Shader_Pipeline to_set_pipe, Ts const&... inshader_pac)
  {
        ,;

      (()),...);
  }*/
