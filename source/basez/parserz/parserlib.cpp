

#include "parserlib.hpp"

unsigned int index_pars(std::string& in_substring,int i)
{
  std::string parsindx;
  std::string index_num = in_substring;
  for(size_t k = 0; k< index_num.size(); k++)
  {
    if(index_num[k]=='[')
    {

      for(int ki = 0; ki <index_num.size()-1; ki++)
      {
        if(index_num[k+ki+1] ==']')
        break;

        parsindx += index_num[k+ki+1];
      }
    }
  }
   unsigned int out_index = stoul(parsindx);
   return out_index;
}

  std::vector<std::string> run_xmlobj_parse(std::string& in_xml_path)
  {
    std::cout <<"\n#->running textture parser func\n";
    std::ifstream texture_config(in_xml_path);
    std::string file_in_string;
    shader_config.seekg(0, std::ios::end);
    file_in_string.reserve(shader_config.tellg());
    shader_config.seekg(0, std::ios::beg);
    file_in_string.assign((std::istreambuf_iterator<char>(texture_config)),
                std::istreambuf_iterator<char>());

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
        return substingz;
  }


/*extra*/
/*
std::vector<shader_tuple_type*>* return_ptr_shader_TV()
{
  return &shader_tuple_vec;
}*/
