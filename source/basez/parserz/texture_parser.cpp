

#include "texture_parser.hpp"


  int texture_xml_lister::run_parse()
  {
    std::cout <<"\n#->running textture parser func\n";
    std::ifstream shader_config("../../shaderglsl/file_list_texture.xml");
    std::string file_in_string;
    shader_config.seekg(0, std::ios::end);
    file_in_string.reserve(shader_config.tellg());
    shader_config.seekg(0, std::ios::beg);
    file_in_string.assign((std::istreambuf_iterator<char>(shader_config)),
                std::istreambuf_iterator<char>());
  }
  std::regex rexal( R"#(\s*<\s*(\S+)\s*>\s*(\S+)\s*<\s*/\1\s*>\s*)#");
  std::vector<std::string> substingz;
  const std::sregex_token_iterator end;
  std::vector<int> indexzr{1,2};

  for(std::sregex_token_iterator reg_iter (file_in_string.begin(), file_in_string.end(), rexal, indexzr);
      reg_iter!=end; ++reg_iter)
      {
        substingz.push_back(*reg_iter);
      }
      for(std::sregex_token_iterator reg_iter (substingz.at(1).begin(), substingz.at(1).end(), rexal, indexzr);
            reg_iter!=end; ++reg_iter)
            {
                substingz.push_back(*reg_iter);
            }
          std::cout <<"->###begin sort\n";
            for(size_t i =0; i<substingz.size(); i++)
            {
              switch(str2int_run(substingz.at(i).c_str()))
              {
                case h_index :
                {
                  break;
                }

                case t_name :
                {
                  break;

                }

                case t_row :
                {
                  break;
                }

                case t_columns :
                {
                  break;
                }

                case t_file_root :
                {
                  break;
                }


              }
