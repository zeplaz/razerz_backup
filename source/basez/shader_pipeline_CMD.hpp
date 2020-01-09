
#include "shader_parser.hpp"





/*
  template<class...Ts>
  void add_shaders_to_pipeline(Shader_Pipeline to_set_pipe, Ts const&... inshader_pac)
  {
        ,;

      (()),...);
  }*/


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
    //const_iterator

    bool create_link_program(std::vector<int>& to_attach_shaders);
    void create_shader(shader_type shad_type, int s_index);
    void setup_shader_code(shader_tuple_type* in_shader_tuple);
    void load_complie(int map_index);

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
     GLuint return_uniform(std::string name)
    {
      auto shearcher = uniform_loc_map.find(name);
      if(shearcher!=uniform_loc_map.end())
      {
        return shearcher->second;
      }
      else{
        std::cerr <<"funtimez uniform not found goina cazedoom!";
        return 254;
      }
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


  class shader_pipeline_CMD
  {
    std::map<unsigned int,gl_shader_t*> master_program_multimap;
    std::unordered_map<Shader_Pipeline,GLuint> Pipline_map;
    //std::map<,std::vector<gl_shader_t*>>

    void add_program_masterlist(unsigned int index,gl_shader_t* shdr_prgm)
    {
      master_program_multimap.insert(std::pair<unsigned int,gl_shader_t*>(index,shdr_prgm));
    }

    gl_shader_t* create_progm_shaderobj()
    {
      gl_shader_t* newsdrprg = new gl_shader_t();
    }

    void remove_shad_prg(unsigned int index)
    {
      std::multimap<unsigned int,gl_shader_t*>::iterator it = master_program_multimap.find(index);

      gl_shader_t* newsdrprg = it->second;
      delete newsdrprg;

      master_program_multimap.erase(it);

    }

    void attach_shader(unsigned int in_program, GLuint in_shader)
    {
      glAttachShader(master_program_multimap.at(in_program)->program_ID,in_shader);
    }

    void use_pipline(Shader_Pipeline to_use_prgm)
    {
      glBindProgramPipeline(Pipline_map.at(to_use_prgm));
    }

    void link_shader_to_prg_seprable(GLuint in_program)
    {
        glProgramParameteri(in_program,GL_PROGRAM_SEPARABLE,GL_TRUE);
        glLinkProgram(in_program);
    }
    void add_pipeline(Shader_Pipeline Pipe_group)
    {
      GLuint pipleline;
      glGenProgramPipelines(1,&pipleline);
      Pipline_map.insert(std::pair<Shader_Pipeline,GLuint>(Pipe_group,pipleline));

    }
  //GL_VERTEX_SHADER_BIT, GL_TESS_CONTROL_SHADER_BIT, GL_TESS_EVALUATION_SHADER_BIT,
  //GL_GEOMETRY_SHADER_BIT,GL_FRAGMENT_SHADER_BIT and GL_COMPUTE_SHADER_BIT. GL_ALL_SHADER_BITS
  void prgm_shder_to_pipe(Shader_Pipeline pipe_group,GLuint program, shader_type to_set)
{
    GLuint pipeline = Pipline_map.at(pipe_group);

      switch(to_set)
      {
        case shader_type::ALL_PIPE :
          {
            glUseProgramStages(pipeline,GL_ALL_SHADER_BITS,program);
            break;
          }
        case shader_type::VERTEX_SHADER :
        {
          glUseProgramStages(pipeline,GL_VERTEX_SHADER_BIT,program);
          break;
        }
        case shader_type::FRAGMENT_SHADER :
        {
            glUseProgramStages(pipeline,GL_FRAGMENT_SHADER_BIT,program);
          break;
        }

        case shader_type::TESS_CONTROL_SHADER :
        {
            glUseProgramStages(pipeline,GL_VERTEX_SHADER_BIT,program);
          break;
        }

        case shader_type::TESS_EVAL_SHADER :
        {
            glUseProgramStages(pipeline,GL_TESS_EVALUATION_SHADER_BIT,program);
          break;
        }

        case shader_type::GEOMETRY_SHADER :
        {
            glUseProgramStages(pipeline,GL_GEOMETRY_SHADER_BIT,program);
          break;
        }

        case shader_type::COMPUTE_SHADER :
        {
            glUseProgramStages(pipeline,GL_VERTEX_SHADER_BIT,program);
          break;
        }
    }
  }
  };
