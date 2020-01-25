#pragma once

#include "../basez/gl_lib_z.hpp"


class feedbacktransform
{
  private :
  bool configured =false;
  std::vector<std::string> varyings;
  char** varyings_out;
  GLuint current_prog_ID;

  public :



/*

void set_shder_prog(GLuint in_id)
  {
    current_prog_ID=in_id;
  }

  const char** const_varyings()
  {
    return  std::add_const<char**> varyings_out;
  }

void  add_varying(std::string in_var)
 {
   varyings.push_back(in_var.c_str());
 }

 void config_varyings()
 {
   if(configured==true)
     {
       delete_underlying();
     }
   if(varyings.empty())
    return;

   //char** vary_temp = new char*[varyings.size()];

   for(int i=0;i<varyings.size();i++)
   {
    // vary_temp = &varyings.at(i).c_str();
   }
    varyings_out = &vary_temp;
    configured = true;

   glTransformFeedbackVaryings(current_prog_ID,varyings.size(),const_varyings(),GL_INTERLEAVED_ATTRIBS);
   glLinkProgram(current_prog_ID);

 }
*/
 void delete_underlying()
 {
    char*   under_v   =*varyings_out;
    delete [] under_v;
 }



};
