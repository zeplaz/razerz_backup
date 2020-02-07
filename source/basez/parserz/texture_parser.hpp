

#include "../gl_lib_z.hpp"
#include "parserlib.hpp"

typedef std::unordered_map<int,texture_tup> t_path_map;

class texture_xml_lister{

  t_path_map texture_path_map;
  //template<class type>

  bool load_run(std::string in_pathxml ="../data_extrn/texture.xml");

  int  registar_texture_path(int id,texture_tup)
  {
    texture_path_map.insert(std::make_pair(id,texture_tup));
  }

  t_path_map* pointer_mapreturn()
  {
    return &texture_path_map;
  }

};
 //std::unique_ptr<t_path_map>  ptr_map = std::make_unique<t_path_map>(texture_path_map);
