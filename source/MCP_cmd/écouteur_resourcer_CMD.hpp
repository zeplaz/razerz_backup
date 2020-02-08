

#include "../basez/parserz/texture_pasrser.hpp"
#include "../basez/texture.hpp"
class texture_ :
{
//  texture_xml_lister t_xml_lister;



};

constexpr std::string Deful_texture_pathlist = "../data_extrn/DEFUL_file_list_texture.xml";
constexpr std::array<std::string,1> text_xml_paths{Deful_texture_pathlist};

  enum Xml_path_index{
    TEXTURE_BIN_DEFULT,
  };

  class texture_ecouteur : public singleton_exd
{
  private :
  std::unordered_map<int,texture_2*> texture_map;
  texture_xml_lister t_xml_lister;

  public :
  void preform_texturexml_scan()
  {
    t_path_map* t_path_m_ptr;

    int parsSTATUS = t_xml_lister.load_run(text_xml_paths.at(TEXTURE_BIN_DEFULT));

    if(parsSTATUS<0)
    {
        std::cerr << "parseerror::" << parsSTATUS << '\n';
        return;
    }

    t_path_m_ptr = t_xml_lister.pointer_mapreturn();

  }

  inline int registar_texture(int index,texture_2& in_texture)
  {
    texture_map.insert(std::make_pair(index,in_texture));
  }



};
