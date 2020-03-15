#pragma once

#include "../basez/shader_parser.hpp"
// NEED TO ADD A SHADER SQUENCER, builds offline,-.loaded into a ref map, for file,
//loading

  
  class shader_pipeline_CMD
  {
    //std::map<unsigned int,gl_shader_t*> master_program_multimap;
    //std::map<,std::vector<gl_shader_t*>>
    protected :
    std::unordered_map<Shader_Pipeline,GLuint> Pipline_map;

    public :

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
    GLuint reutun_pipeline_ID(Shader_Pipeline to_use_prgm)
    {
      return Pipline_map.at(to_use_prgm);
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

    if((shader_type::FRAGMENT_SHADER & to_set)==shader_type::FRAGMENT_SHADER)
    {
      std::cout<<"fragshaderfound\n";
      glUseProgramStages(pipeline,GL_FRAGMENT_SHADER_BIT,program);
    }

    if((shader_type::VERTEX_SHADER & to_set)==shader_type::VERTEX_SHADER)
    {
      std::cout <<"verted shaderfound!\n";
      glUseProgramStages(pipeline,GL_VERTEX_SHADER_BIT,program);
    }

    if((shader_type::COMPUTE_SHADER & to_set)==shader_type::COMPUTE_SHADER)
    {
    std::cout <<"compute shaderfound!\n";
    glUseProgramStages(pipeline,GL_VERTEX_SHADER_BIT,program);
    }

    if((shader_type::ALL_PIPE & to_set)==shader_type::ALL_PIPE)
    {

      std::cout <<"all shaderfound!\n";
      glUseProgramStages(pipeline,GL_ALL_SHADER_BITS,program);
    }

    if((shader_type::GEOMETRY_SHADER & to_set)==shader_type::GEOMETRY_SHADER)
    {
      std::cout <<"all shaderfound!\n";
      glUseProgramStages(pipeline,GL_GEOMETRY_SHADER_BIT,program);
    }


    if((shader_type::TESS_EVAL_SHADER & to_set)==shader_type::TESS_EVAL_SHADER)
    {

      std::cout <<"tessleval shaderfound!\n";
      glUseProgramStages(pipeline,GL_TESS_EVALUATION_SHADER_BIT,program);
    }

    if((shader_type::TESS_CONTROL_SHADER & to_set)==shader_type::TESS_CONTROL_SHADER)
    {
     std::cout <<"teslcontrl shaderfound\n";
     glUseProgramStages(pipeline,GL_TESS_CONTROL_SHADER_BIT,program);
    }
  }
  };


  /*  void add_program_masterlist(unsigned int index,gl_shader_t* shdr_prgm)
    {
      master_program_multimap.insert(std::pair<unsigned int,gl_shader_t*>(index,shdr_prgm));
    }*/
