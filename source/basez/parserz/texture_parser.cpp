

#include "texture_parser.hpp"




  bool texture_xml_lister::load_run(std::string in_pathxml)
      {
        std::vector<std::string> substringoutput;
        substringoutput   = run_xmlobj_parse(in_pathxml);

        std::cout <<"->###begin sort\n";

        for(size_t i =0; i<substringoutput.size(); i++)
          {
            switch(str2int_run(substringoutput.at(i).c_str()))
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
          }
}
