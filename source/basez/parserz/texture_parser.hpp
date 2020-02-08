

#include "../gl_lib_z.hpp"
#include "parserlib.hpp"


class texture_xml_lister{

  tt_map texture_tupl_map;
  //template<class type>

  int load_run(std::string in_pathxml);

  inline int  registar_texture_tupl(int id,texture_tupl)
  {
    texture_path_map.insert(std::make_pair(id,texture_tup));
  }

  inline tt_map* pointer_mapreturn()
  {
    return &texture_path_map;
  }

};
 //std::unique_ptr<t_path_map>  ptr_map = std::make_unique<t_path_map>(texture_path_map);
