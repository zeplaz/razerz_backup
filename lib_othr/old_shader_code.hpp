
/*
OLD OR DEPREATED SHADER CODE
*/





/*
DEPREATED SHADER CLASS>..?
*/

class gl_shader
{
  private :
  std::string shader_code_vertex;
  std::string shader_code_fragment;
  std::string shader_code_compute;

  shader_type s_type;
  public :
  GLuint program_ID = 0;
  GLuint shader_pos;
  GLuint shader_colour;

  GLuint vertex_shader_ID;
  GLuint frag_shader_ID;

  void create_shader(shader_type shad_type);
  void get_shader_code(const std::string &path,shader_type type);
  void load_shader_complie();
  void set_attrabutes(GLuint&gl_prgm);

  inline void use_shader()
  {
    glUseProgram(program_ID);
  }

  inline void get_strd_shader_code(std::string in_path,shader_type type)
  {
   if(type ==shader_type::VERTEX_SHADER)
    {
      shader_code_vertex = in_path;
    }

   else if(type ==shader_type::FRAGMENT_SHADER)
     {
       shader_code_fragment = in_path;
     }

     else if(type ==shader_type::COMPUTE_SHADER)
       {
         shader_code_compute = in_path;
       }

     s_type = type;
  }
};

void gl_shader::create_shader(shader_type shad_type)
{
  if(shad_type ==shader_type::VERTEX_SHADER)
  {vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);}

  else if(shad_type ==shader_type::FRAGMENT_SHADER)
  {frag_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);}

}

  void  gl_shader::set_attrabutes(GLuint&gl_prgm)
   {
     shader_pos = glGetAttribLocation(gl_prgm,"positions");
     shader_colour = glGetAttribLocation(gl_prgm,"vertexColour");
   }


  void gl_shader::get_shader_code(const std::string &path,shader_type type)
  {
     std::ifstream file(path);
     std::string ret = "";
     std::string line_buff ="";
     if(file.is_open())
     {
      ret= std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
        /*
           while (gfile)
           { std::getline(file,line_buff);
             ret += line_buff+"\n";
           }
           */
         //  {ret+line+'\n';}
       std::cout << ret;
       file.close();
     }
     s_type =type;
     if(type ==shader_type::VERTEX_SHADER)
      shader_code_vertex = ret;

     else if(type ==shader_type::FRAGMENT_SHADER)
       shader_code_fragment = ret;
   }

   void gl_shader::load_shader_complie()
   {
     std::cout <<"\n->###LOAD-COMPLING NEW SHADER\n";
     GLint vertex_compiled;
     GLint fragment_complied;
     GLchar* log_shader;
    // std::cout << "loading newshader:\n";
     if(s_type ==shader_type::VERTEX_SHADER)
     {
       const GLchar*  sh_gl_vrx = shader_code_vertex.c_str();
       glShaderSource(vertex_shader_ID,1,&sh_gl_vrx,NULL);
       glCompileShader(vertex_shader_ID);
       glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &vertex_compiled);

       if (vertex_compiled != GL_TRUE)
       {
        GLint logsize;
        std::cout <<"falure to vertix_complie";
        glGetShaderiv(vertex_shader_ID,GL_INFO_LOG_LENGTH,&logsize);
        log_shader = new GLchar[logsize+1];

        glGetShaderInfoLog(vertex_shader_ID, logsize, NULL, log_shader);
        // Write the error to a log
        std::cout << log_shader<< '\n';
        delete log_shader;
       }
     }
     else if(s_type ==shader_type::FRAGMENT_SHADER)
     {
       const GLchar*  sh_gl_frag = shader_code_vertex.c_str();

       glShaderSource(frag_shader_ID,1,&sh_gl_frag,NULL);
       glCompileShader(frag_shader_ID);
       glGetShaderiv(frag_shader_ID, GL_COMPILE_STATUS, &fragment_complied);

       if (fragment_complied == GL_TRUE)
       {
        GLint logsize;
        std::cout <<"falure to vertix_complie";
        glGetShaderiv(frag_shader_ID,GL_INFO_LOG_LENGTH,&logsize);
        log_shader = new GLchar[logsize+1];

        glGetShaderInfoLog(frag_shader_ID, logsize, NULL, log_shader);
        // Write the error to a log
        std::cout << log_shader<< '\n';
        delete log_shader;
       }
     }
     std::cout <<"\n->###LOAD-COMPLING COMPLEATE \n\n";
   }
