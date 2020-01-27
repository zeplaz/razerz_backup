#pragma once

#include "../basez/gl_lib_z.hpp"
#include <utility>
#include <type_traits>


class feedbacktransform
{
  private :
  bool configured =false;
  std::vector<std::string> varyings;
  std::vector<const char*> varyings_out;
  GLuint current_prog_ID;

  public :

  void config_varyings();
  void delete_underlying();

  inline void set_shder_prog(GLuint in_id)
  {
    current_prog_ID=in_id;
  }

  inline void  add_varying(std::string in_var)
  {
   varyings.push_back(in_var.c_str());
  }

   void configure_feedback_pass(GLuint in_prog_id,std::vector<std::string>* varrying_set);

};

 void configure_feedback_pass(feedbacktransform* fbtf,GLuint in_prog_id,std::vector<std::string>* varrying_set);
