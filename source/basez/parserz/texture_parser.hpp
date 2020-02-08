

#include "../gl_lib_z.hpp"
#include "parserlib.hpp"


shader_tuple_type* new_tt_ptr()
{
    texture_tup* tt_ptr = new texture_tup();
  //  shader_tuple_vec.push_back(shader_tuple_ptr);
    *shader_tuple_ptr = std::make_tuple(0,"","","");
      //shader_tuple_map.insert(pair<unsigned int,shader_tuple_type*>(,shader_tuple_ptr));
  //std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return shader_tuple_ptr;
}


class texture_xml_parser{

  tt_map texture_tupl_map;

  int load_run(std::string in_pathxml);
  GLEnum subtype_toGLenumtexture(const std::string& in_substring);
  inline int  registar_texture_tupl(unsigned int id,texture_tupl)
  {
    texture_path_map.insert(std::make_pair(id,texture_tup));
  }

  inline tt_map* pointer_mapreturn()
  {
    return &texture_path_map;
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
