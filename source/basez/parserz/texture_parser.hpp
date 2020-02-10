
#include "../gl_lib_z.hpp"
#include "parserlib.hpp"

texture_tupl* new_tt_ptr()
{
    texture_tupl* tt_ptr = new texture_tupl();
    //  shader_tuple_vec.push_back(shader_tuple_ptr);
    //inteximage2d* inti2d = new inteximage2d();
    *tt_ptr = std::make_tuple(NULL_TT);
  //shader_tuple_map.insert(pair<unsigned int,shader_tuple_type*>(,shader_tuple_ptr));
  //std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return tt_ptr;
}



class xml_parser{

public :
int load_run(std::string in_pathxml);
GLEnum subtype_toGLenumtexture(const std::string& in_substring);

};
class texture_xml_parser :public : xml_parser{

  tt_map texture_tupl_map;

  inline int  registar_texture_tupl(unsigned int id,texture_tupl)
  {
    texture_path_map.insert(std::make_pair(id,texture_tup));
  }

  inline tt_map* pointer_mapreturn()
  {
    return &texture_path_map;
  }

  int gen_teximage(std::string& in_substring,unsigned int index,int str_pos)
  {
    texture_tupl* curr_text_tup;

    curr_text_tup = new_tt_ptr();
    std::get<TT_INDEX>(*curr_text_tup) = index;

    teximage2d_parmz* current_ti2d_parmz = std::get<TEXIMG_PARAMZ>(*in_tt);

    texture_tupl_map.insert(std::make_pair(index,curr_text_tup));

    for(int i = str_pos; i<in_substring.size();i++)
    {
      switch(str2int_run(in_substring.at(i).c_str()))
      {
        case subtype :
        {
          std::get<TT_SUB_TYPE>(*curr_text_tup) = subtype_toGLenumtexture(substingz.at(i+1));
          break;
        }

        }
        case :
        {
          break;
        }
      }


    }

  }

  void remove_tt(unisgned int id)
  {
    texture_tupl_map.find(id)
    it = texture_tupl_map.find(id);
    if (it != texture_tupl_map.end())
    {
      texture_tup* tt_ptr = it->second;
      delete [] texture_tup;
      texture_tupl_map.erase (it);
    }
  }
};
 //std::unique_ptr<t_path_map>  ptr_map = std::make_unique<t_path_map>(texture_path_map);
