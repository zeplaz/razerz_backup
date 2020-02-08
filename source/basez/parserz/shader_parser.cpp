
#include "shader_parser.hpp"


shader_tuple_type* return_new_shader_tuple()
{
    shader_tuple_type* shader_tuple_ptr = new shader_tuple_type();
  //  shader_tuple_vec.push_back(shader_tuple_ptr);
    *shader_tuple_ptr = std::make_tuple(0,shader_type::SHADER_NULL,"","");
      //shader_tuple_map.insert(pair<unsigned int,shader_tuple_type*>(,shader_tuple_ptr));
  //std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return shader_tuple_ptr;
}


std::map<unsigned int,shader_tuple_type*>* return_shdrmap_ptr_TV()
{
  return &shader_tuple_map;
}


void size_of_tuplevec()
{
  std::cout << "\n of vec size:final" << shader_tuple_map.size() <<'\n';
}

/*
SHADER run PARSE GLOBAL
*/
int run_parse()
{
  std::vector<std::string> substingz = run_xmlobj_parse("../shaderglsl/file_list_shader.xml");

  std::string_view sub_string_view{substingz.c_str(), substingz.size()};

  shader_tuple_type* current_tuple_prt;

  std::cout <<"->###begin sort\n";
//
    for(size_t i =0; i<substingz.size(); i++)
    {
      switch(str2int_run(substingz.at(i).c_str()))
      {
        case h_shad_title :
        {

          std::cout << "newSHADER!:\n";
          break;
        }
        case h_index :
        {
          current_tuple_prt = return_new_shader_tuple();
          unsigned int  temp_index = index_pars(sub_string_view);
            //std::get<0>(*current_tuple_prt) =temp_index;

           std::cout << "shaderrawindex::"<< substingz.at(i+1) <<'\n';
           std::cout << "shaderindexnum::"<< temp_index <<'\n';
           std::get<ST_INDEX>(*current_tuple_prt) = temp_index;
           shader_tuple_map.insert(std::pair<unsigned int,shader_tuple_type*>(temp_index,current_tuple_prt));

          break;
        }

        case h_shad_type :
        {
          std::cout << "shaderType:::"<< substingz.at(i+1)  <<'\n';
          if (substingz.at(i+1) =="vertex")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::VERTEX_SHADER;
          }
          else if (substingz.at(i+1) =="fragment")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::FRAGMENT_SHADER;
          }
          else if (substingz.at(i+1) =="compute")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::COMPUTE_SHADER;
          }
          break;
        }
        case h_file_root :
         {
           std::cout << "shader_source_loc::"<< substingz.at(i+1) <<'\n';
          std::get<ST_FILEPATH>(*current_tuple_prt) = substingz.at(i+1);
          break;
         }

         case h_shad_name :
          {
            std::cout << "shadername::"<< substingz.at(i+1) <<'\n';
           std::get<ST_NAME>(*current_tuple_prt) = substingz.at(i+1);
           break;
          }
        }
}
std::cout << "\n #####shader parser run compleate of vec size:final::" << shader_tuple_map.size() <<'\n' <<'\n';
return 0;
}


/*

           std::string parsindx;
           std::string index_num = substingz.at(i+1);
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
            unsigned int  temp_index = stoul(parsindx);
*/
/*

std::cout <<"\nrunning shader parser func\n";
std::ifstream shader_config("../shaderglsl/file_list_shader.xml");
std::string file_in_string;
shader_config.seekg(0, std::ios::end);
file_in_string.reserve(shader_config.tellg());
shader_config.seekg(0, std::ios::beg);

file_in_string.assign((std::istreambuf_iterator<char>(shader_config)),
            std::istreambuf_iterator<char>());
std::cout <<"###shderpart1\n";
//std::regex rexal( R"#(\s*<\s*(\S+)\s*>\s*(\S+)\s*<\s*///\1\s*>\s*)#");*/
/*
std::vector<std::string> substingz;
const std::sregex_token_iterator end;
std::vector<int> indexzr{1,2};

std::cout <<"###shderpart2\n";
for(std::sregex_token_iterator reg_iter (file_in_string.begin(), file_in_string.end(), rexal, indexzr);
    reg_iter!=end; ++reg_iter)
    {
      substingz.push_back(*reg_iter);
    }
std::cout <<"###shderpart3\n";
for(std::sregex_token_iterator reg_iter (substingz.at(1).begin(), substingz.at(1).end(), rexal, indexzr);
      reg_iter!=end; ++reg_iter)
      {
          substingz.push_back(*reg_iter);
      }


*/
