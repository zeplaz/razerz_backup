

#include "shader_parser.hpp"


constexpr unsigned int str2int(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

 unsigned int str2int_run(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

constexpr unsigned int h_index = str2int("INDEX");
constexpr unsigned int h_shad_type = str2int("SHADER_TYPE");
constexpr unsigned int h_file_root = str2int("file_root");
constexpr unsigned int h_shad_name = str2int("NAME");
constexpr unsigned int h_shad_title = str2int("shader_glsl");


void size_of_tuplevec()
{
  std::cout << "\n of vec size:final" << shader_tuple_vec.size() <<'\n';
}

std::vector<shader_tuple_type*>* return_ptr_shader_TV()
{
  return &shader_tuple_vec;
}

shader_tuple_type* return_new_shader_tuple()

{
    shader_tuple_type* shader_tuple_ptr = new shader_tuple_type();

    shader_tuple_vec.push_back(shader_tuple_ptr);

    *shader_tuple_ptr = std::make_tuple(0,shader_type::SHADER_NULL,"","");
  std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return shader_tuple_ptr;
}

void gl_shader_t::create_shader(shader_type shad_type, int s_index)
{ std::cout <<"creating shader gl\n";
  if(shad_type == shader_type::VERTEX_SHADER)
  {

    GLuint shader_ID = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "NEW VERTEX SHADER GENREATING\n";
    std::pair<shader_type,GLuint> temp_shard = std::make_pair(shad_type,shader_ID);
    std::cout << "->inserting shaderID intomap::" <<s_index << '\n';
    shader_IDz_map.insert(std::make_pair(s_index,temp_shard));
    contained_shaders |=shader_type::VERTEX_SHADER;
  }

  if(shad_type ==shader_type::FRAGMENT_SHADER)
  {
    std::cout << "NEW FRAGMENT SHADER GENREATING\n";
    shader_IDz_map.insert(std::make_pair(s_index,std::make_pair(shader_type::FRAGMENT_SHADER,glCreateShader(GL_FRAGMENT_SHADER))));
    std::cout << "->inserting shaderID intomap::" <<s_index << '\n';
    contained_shaders |=shader_type::FRAGMENT_SHADER;
  }
}


int run_parse()
{
  std::ifstream shader_config("shaderglsl/file_list_shader.xml");
  std::string file_in_string;
  shader_config.seekg(0, std::ios::end);
  file_in_string.reserve(shader_config.tellg());
  shader_config.seekg(0, std::ios::beg);

  file_in_string.assign((std::istreambuf_iterator<char>(shader_config)),
              std::istreambuf_iterator<char>());

  std::regex rexal( R"#(\s*<\s*(\S+)\s*>\s*(\S+)\s*<\s*/\1\s*>\s*)#");
  std::vector<std::string> substingz;
  const std::sregex_token_iterator end;
  std::vector<int> indexzr{1,2};

  for(std::sregex_token_iterator reg_iter (file_in_string.begin(), file_in_string.end(), rexal, indexzr);
      reg_iter!=end; ++reg_iter)
      {
        substingz.push_back(*reg_iter);
      }

  for(std::sregex_token_iterator reg_iter (substingz.at(1).begin(), substingz.at(1).end(), rexal, indexzr);
        reg_iter!=end; ++reg_iter)
        {
            substingz.push_back(*reg_iter);
        }

      shader_tuple_type* current_tuple_prt;

    for(size_t i =0; i<substingz.size(); i++)
    {
      switch(str2int_run(substingz.at(i).c_str()))
      {
        case h_shad_title :
        {

          std::cout << "newSHADER!:\n";
          break;
        }
        case h_index :
        {  current_tuple_prt = return_new_shader_tuple();

           std::string parsindx;
           std::string index_num = substingz.at(i+1);
           for(size_t k = 0; k< index_num.size(); k++)
           {
             if(index_num[k]=='[')
             {

               for(int ki = 0; ki <index_num.size()-1; ki++)
               {
                 if(index_num[k+ki+1] ==']')
                 break;

                 parsindx += index_num[k+ki+1];
               }
             }
           }
            unsigned int  temp_index = stoul(parsindx);
            //std::get<0>(*current_tuple_prt) =temp_index;
            std::cout << "shaderrawindex::"<< substingz.at(i+1) <<'\n';
            std::cout << "shaderindexnum::"<< temp_index <<'\n';
            std::get<0>(*current_tuple_prt) = temp_index;
            break;
        }

        case h_shad_type :
        {
          std::cout << "shaderType:::"<< substingz.at(i+1)  <<'\n';
          if (substingz.at(i+1) =="vertex")
          {
            std::get<1>(*current_tuple_prt) = shader_type::VERTEX_SHADER;
          }
          else if (substingz.at(i+1) =="fragment")
          {
            std::get<1>(*current_tuple_prt) = shader_type::FRAGMENT_SHADER;
          }
          break;
        }
        case h_file_root :
         {
           std::cout << "shader_source_loc::"<< substingz.at(i+1) <<'\n';
          std::get<2>(*current_tuple_prt) = substingz.at(i+1);
          break;
         }

         case h_shad_name :
          {
            std::cout << "shadername::"<< substingz.at(i+1) <<'\n';
           std::get<3>(*current_tuple_prt) = substingz.at(i+1);
           break;
          }
        }

}
std::cout << "\n of vec size:final" << shader_tuple_vec.size() <<'\n';
return 0;
}

void gl_shader::create_shader(shader_type shad_type)
{
  if(shad_type ==shader_type::VERTEX_SHADER)
  {vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);}

  if(shad_type ==shader_type::FRAGMENT_SHADER)
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

     GLint vertex_compiled;
     GLint fragment_complied;
     GLchar* log_shader;
     std::cout << "loading newshader:\n";
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
   }
