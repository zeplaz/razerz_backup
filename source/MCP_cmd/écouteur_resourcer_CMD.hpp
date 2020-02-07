

#include "../basez/parserz/texture_pasrser.hpp"
#include "../basez/texture.hpp"
class texture_ :
{
//  texture_xml_lister t_xml_lister;



};

  class texture_ecouteur : public singleton_exd
{

  std::unordered_map<int,texture_2*> texture_map;

  texture_xml_lister t_xml_lister;

  void preform_texturexml_scan()
  {
    t_path_map* t_path_m_ptr;

    int parsSTATUS = t_xml_lister.run_parse();

    if(parsSTATUS<0)
    {
        std::cerr << "parseerror::" << parsSTATUS << '\n';
        return;
    }

     t_path_m_ptr = t_xml_lister.pointer_mapreturn();
     

  }

  int registar_texture()
  {
    texture_map.insert(std::make_pair())
  }



};
