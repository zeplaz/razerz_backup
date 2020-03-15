
#include "texture_parser.hpp"


int texture_xml_parser::item_selection(std::string& in_obj_type,std::vector<std::string>& in_substingz,unsigned int index,int str_pos)
{
  texture_tupl* curr_text_tup;
  curr_text_tup = new_tt_ptr();

  texture_tupl_map.insert(std::make_pair(index,curr_text_tup));

  for(int i = str_pos; i<in_substring.size();i++)
  {
    switch(str2int_run(in_substring.at(i).c_str()))
    {
      case subtype :
      {
        if(in_substingz.at(i+1) == "texture2d")
        {
          teximage2d_parmz* ti2d_prmz  =&std::get<TEXIMG_PARAMZ>(*curr_text_tup);
          std::get<TI2D_TARGET>(*ti2d_prmz) = subtype_toGLenumtexture(in_substingz.at(i+1));
          //gen_teximage(in_substingz,i);
        }
        break;
      }

      //not in right place!!
      case t_colour_comp :
      {
        std::get<TI2D_COLOUR_COMP>(*ti2d_prmz) = colour_comp_toGLint(in_substingz.at(i+1));
        break;
      }

      case t_pix_formate :
        {
          std::get<TI2D_PIX_FORMATE>(*ti2d_prmz)  =
        break;
        }
        case t_pixdata_type :
        {
          std::get<TI2D_PIX_DATATYPE>(*ti2d_prmz) =
        break;
        }

      case name :
        {
         std::get<TT_NAME>(*curr_text_tup) = in_substingz.at(i+1);
        break;
        }

      case file_root :
        {
         std::get<TT_FILEPATH>(*curr_text_tup) = in_substingz.at(i+1);
        break;
        }

      case flagz :
        {
          std::get<TT_FLAGZ>(*curr_text_tup) = (unsigned char)in_substingz.at(i+1);
          return i;
        break;
        }
      }//endswitch
    }//end//for
}


int texture_xml_parser::gen_teximage(std::string& in_substring,int i)
{
  //teximage2d_parmz* current_ti2d_parmz = std::get<TEXIMG_PARAMZ>(*in_tt);

}

GLint colour_comp_toGLint(const std::string& in_substring)
{
  if(in_substring=="inf_depth")
  {
    return GL_DEPTH_COMPONENT;
  }
  if(in_substring=="inf_depth+sten")
  {
    return GL_DEPTH_STENCIL;
  }
  if(in_substring=="inf_rgba")
  {
    return GL_RGBA;
  }
  if(in_substring=="inf_red")
  {
    return GL_RED;
  }
  if(in_substring=="inf_srgba8")
  {
    return GL_SRGB8_ALPHA8;
  }
  if(in_substring=="inf_rgba16")
  {
    return GL_RGBA16;
  }
  if(in_substring=="inf_rgba32f")
  {
    return GL_RGBA32F;
  }

  if(in_substring=="inf_inf_rgba16f")
  {
    return GL_RGBA16F;
  }
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
