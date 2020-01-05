
#include "geometry_parser.hpp"


int main(int argc, char* argv[])
{
  std::regex check_formate_OBJ("OBJ File",
  std::regex_constants::ECMAScript | std::regex_constants::icase);

  std::regex get_name_next_obj("o",
  std::regex_constants::ECMAScript | std::regex_constants::icase);

  Wavefront_parser wp;

//parser
ply_parser pp;
  pp.open_read_file("bbaz.ply");
  std::cout << "num of vertexz::" << pp.num_of_vertex_points() <<'\n';
  std::cout << "num of indices::" << pp.num_of_indices() <<'\n';
pp.dump_data_terminal_at(0);

std::vector<float> verx_da_test2 = pp.return_vertex_xyz_data();
std::vector<unsigned int> indices_da_test2 = pp.return_indices_data();
return 0;
}
  //std::regex_iterator<std::string::iterator> end;
