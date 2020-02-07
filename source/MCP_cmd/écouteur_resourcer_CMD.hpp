

#include "parserz/texture_pasrser.hpp"

class texture_file_ecouteur : public singleton_exd
{
  texture_xml_lister t_xml_lister;

  std::unordered_map<int,texture_tup> texture_path_map;

  void preform_texturexml_scan()
  {
    int parsSTATUS = t_xml_lister.run_parse(texture_path_map);

  }

  void registar_texture_path(int id,texture_tup)
  {

    texture_path_map.insert(int id,texture_tup);

   }

};
