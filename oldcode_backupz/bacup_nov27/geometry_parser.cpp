#include "geometry_parser.hpp"


void ply_parser::open_read_file(std::string fname)
{

  //r_file.open(fname,std::ios::in);

  std::ifstream ifs(fname.c_str(), std::ios::in | std::ios::ate);

  std::ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  std::string raw_data(bytes.data(), fileSize);
  ifs.close();

  std::regex el_ver_match("\\b(element vertex) \\s*(\\S+)");
  std::regex el_face_match("\\b(element face) \\s*(\\S+)");
  //std::regex el_face_match("\\b(end_header) \\s*(\\S+)");

  std::regex num_extractor("\\b\\d+\\b");


  std::regex_iterator<std::string::iterator> it01(raw_data.begin(),
                                                  raw_data.end(), el_ver_match);

  std::cout << it01->str() << '\n';

  std::string extrc_string = it01->str();
  std::regex_iterator<std::string::iterator> it02(extrc_string.begin(),
                                                  extrc_string.end(), num_extractor);

  std::cout << it02->str() << '\n';
  unsigned int element_vertex = std::stoi(it02->str());

  std::regex_iterator<std::string::iterator> it03(raw_data.begin(),
                                                  raw_data.end(),el_face_match);
  std::cout << it03->str() << '\n';

  extrc_string = it03->str();
  std::regex_iterator<std::string::iterator> it04(extrc_string.begin(),
                                                  extrc_string.end(), num_extractor);
   std::cout << it04->str() << '\n';
   unsigned int element_face = std::stoi(it04->str());

   std::regex end_head("\\b(end_header)");
   //<=\\n\\d[^\\n]*
   std::smatch matcher;
   std::regex_search ( raw_data,matcher,end_head );
   matcher.position(0);
   std::regex_iterator<std::string::iterator> it05(raw_data.begin(),
                                                   raw_data.end(), end_head);
    std::cout <<  it05->str() <<  " at pos"  << matcher.position(0) << '\n';
    int end_header_pos = matcher.position(0)+11;

    ifs.open(fname,std::ios::in);
    ifs.seekg(end_header_pos, std::ios::beg);
    std::string line ="";
    element_vertex_tuple evt;

    for(size_t i =0; i<element_vertex;i++)
    {
      std::array<float,3> e_verx_xyz;
      std::array<float,3> e_norm_ver_xxyz;
      std::array<float,2> e_text_cord;
      std::getline(ifs,line);
      std::istringstream iss(line);

      iss >> e_verx_xyz[0] >> e_verx_xyz[1] >>  e_verx_xyz[2]
          >> e_norm_ver_xxyz[0] >> e_norm_ver_xxyz[1] >> e_norm_ver_xxyz[2]
          >> e_text_cord[0] >> e_text_cord[1];
          //std::cout <<"xyz" << e_verx_xyz[0] << e_verx_xyz[1] <<  e_verx_xyz[2] << '\n';

    evt = std::make_tuple(e_verx_xyz,e_norm_ver_xxyz,e_text_cord);
    evt_vec.push_back(evt);
    }


    for(size_t i =0; i<element_face;i++)
    {
     std::array<unsigned int,4> e_face_indices;
      std::getline(ifs,line);
      std::istringstream iss(line);
      iss >> e_face_indices[0] >> e_face_indices[1] >> e_face_indices[2]
          >> e_face_indices[3];
    e_indices_list.push_back(e_face_indices);
    }

}
