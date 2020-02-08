

#include "texture_parser.hpp"

shader_tuple_type* new_tt_ptr()
{
    texture_tup* tt_ptr = new texture_tup();
  //  shader_tuple_vec.push_back(shader_tuple_ptr);
    *shader_tuple_ptr = std::make_tuple(0,"","","");
      //shader_tuple_map.insert(pair<unsigned int,shader_tuple_type*>(,shader_tuple_ptr));
  //std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return shader_tuple_ptr;
}


  bool texture_xml_lister::load_run(std::string in_pathxml)
      {
        std::vector<std::string> substingz = run_xmlobj_parse(in_pathxml);
        std::string_view sub_string_view{substingz.c_str(), substingz.size()};
        texture_tup* curr_text_tup;

    std::cout <<"->###begin sort\n";

        for(size_t i =0; i<substingz.size(); i++)
          {
            switch(str2int_run(substingz.at(i).c_str()))
              {
                case index :
                {
                  curr_text_tup = new_tt_ptr();
                  unsigned int  temp_index = index_pars(sub_string_view);
                  std::cout << "ttrawindex::"<< substingz.at(i+1) <<'\n';
                  std::cout << "ttindexnum::"<< temp_index <<'\n';

                  std::get<TT_INDEX>(*curr_text_tup) = temp_index;
                  texture_tupl_map.insert(std::make_pair(temp_index,curr_text_tup));

                break;
                }

                case item_type :
                {
                  break;

                }

                case t_name :
                {
                  break;
                }

                case t_file_root :
                {

                  break;
                }

                case t_file_root :
                {
                  break;
                }
            }
          }
}
