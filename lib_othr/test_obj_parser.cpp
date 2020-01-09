
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



  //from colour.hpp




  void test_bimaskswitch(std::array<shader_type,4> in_topass)
  {
  for(int i = 0; i<in_topass.size(); i++)
  {
  std::cout <<'\n'<<'\n' << "i:"<< i <<'\n';
  if(i==0)
  {
    std::cout <<"idnex for COMPUTE_SHADER::\n";
  }
  if(i==1)
  {
    std::cout <<"idnex for::tvetzAND_frag\n";
  }
  if(i==2)
  {
    std::cout <<"idnex for::tall_test\n";
  }
  if(i==3)
  {
    std::cout <<"idnex for::passed_sh_type1\n";
  }
  if((shader_type::FRAGMENT_SHADER & in_topass[i])==shader_type::FRAGMENT_SHADER)
  {
    std::cout<<"fragshaderfound\n";
  }

  if((shader_type::VERTEX_SHADER & in_topass[i])==shader_type::VERTEX_SHADER)
  {
    std::cout <<"verted shaderfound!\n";
  }

  if((shader_type::COMPUTE_SHADER & in_topass[i])==shader_type::COMPUTE_SHADER)
  {
  std::cout <<"compute shaderfound!\n";
  }

  if((shader_type::ALL_PIPE & in_topass[i])==shader_type::ALL_PIPE)
  {
    std::cout <<"all shaderfound!\n";
  }
  }
  }
