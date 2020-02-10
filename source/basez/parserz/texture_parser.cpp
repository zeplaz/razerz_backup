
#include "texture_parser.hpp"

   bool xml_parser::load_run(std::string in_pathxml)
   {
      std::vector<std::string> substingz = run_xmlobj_parse(in_pathxml);
      {substingz.c_str(), substingz.size()};


      std::cout <<"->###begin sort\n";
      unsigned int current_0jk_index;

      for(size_t i =0; i<substingz.size(); i++)
        {
          switch(str2int_run(substingz.at(i).c_str()))
            {
              case index :
                {
                  //std::string_view sub_string_view {substingz.at(i+1).c_str(),
                  current_0jk_index = index_pars(substingz.at(i),i);
                  std::cout << "ttrawindex::"<< substingz.at(i+1) <<'\n';
                  std::cout << "ttindexnum::"<< current_0jk_index <<'\n';

                break;
                }

              case item_type :
                {
                  if(substingz.at(i+1) =="texture")
                  {
                  i  = gen_teximage();
                  }
                  gen_teximage_paramz()
                  //inteximage2d* curr_teximg =
                break;
                }


              case t_name :
                {
                  std::get<TT_NAME>(*curr_text_tup) = substingz.at(i+1);
                break;
                }

              case t_file_root :
                {
                  std::get<TT_FILEPATH>(*curr_text_tup) = substingz.at(i+1);
                break;
                }

              case flagz :
                {
                  std::get<TT_FLAGZ>(*curr_text_tup) = (unsigned char)substingz.at(i+1);
                break;
                }
          }//endswitch
        }//endfor
}

GLEnum texture_xml_parser::subtype_toGLenumtexture(const std::string& in_substring)
{
  if(in_substring== "texture1d")
  {
    return GL_TEXTURE_1D;
  }
  else if(in_substring== "texture2d")
  {
    return GL_TEXTURE_2D;
  }
  else if(in_substring== "texture3d")
  {
    return GL_TEXTURE_3D;
  }
 else if(in_substring== "texturerec")
  {
    return GL_TEXTURE_RECTANGLE;
  }
  else if(in_substring== "texturebuff")
  {
    return GL_TEXTURE_BUFFER;
  }
  else if(in_substring== "texturecubmap")
  {
    return GL_TEXTURE_CUBE_MAP;
  }
  else if(in_substring== "texture1d_array")
  {
    return GL_TEXTURE_1D_ARRAY;
  }
  else if(in_substring== "texture2d_array")
  {
    return GL_TEXTURE_2D_ARRAY;
  }
  else if(in_substring== "texturecubmap_array")
  {
    return GL_TEXTURE_CUBE_MAP_ARRAY;
  }

  else if(in_substring== "texture2d_multi")
  {
    return GL_TEXTURE_2D_MULTISAMPLE;
  }

  else if(in_substring== "texture2d_multi_array")
  {
    return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
  }
}
