
#ifndef  REZ_UTIL_HPP
#define REZ_UTIL_HPP

#include "io_utilityz.hpp"
//pars paramz >- some can be moved into own xmlfiles later..
enum Xml_path_index{
  TEXTURE_BIN_DEFULT,
  MODEL_BIN_DEFULT,
  MESH_BIN_DEFULT,
  SCENE_BIN_DEFULT
};

constexpr std::string Deful_texture_pathlist = {"../data_extrn/DEFUL_file_list_texture.xml"};

//constexpr std::string_view Def_tex_path_view(Deful_texture_pathlist);
//constexpr std::array<std::string_view,1> text_xml_paths{Deful_texture_pathlist};


#endif
