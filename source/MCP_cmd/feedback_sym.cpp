#include "feedback_sym.hpp"

 void feedbacktransform::config_varyings()
 {
   if(configured==true)
     {
       delete_underlying();
     }
   if(varyings.empty())
    {return;}

    std::transform(std::begin(varyings), std::end(varyings),
               std::back_inserter(varyings_out), std::mem_fn(&std::string::c_str));
    //const char** con_varz= const_cast<char**>(varyings_out);

   glTransformFeedbackVaryings(current_prog_ID,varyings.size(),varyings_out.data(),GL_INTERLEAVED_ATTRIBS);
   glLinkProgram(current_prog_ID);
   configured = true;
 }

 void feedbacktransform::delete_underlying()
 {
   for(int i =0; i<varyings_out.size();i++)
   {
       const char*   under_v   =varyings_out[i];
       delete[] under_v;

   }
    varyings_out.erase(varyings_out.end(),varyings_out.begin());


 }

 void feedbacktransform::configure_feedback_pass(GLuint in_prog_id,std::vector<std::string>* varrying_set)
{
  this->set_shder_prog(in_prog_id);
  for(int i =0; i< varrying_set->size();i++)
  {
    this->add_varying(varrying_set->at(i));
  }
  this->config_varyings();
}

 void configure_feedback_pass(feedbacktransform* fbtf,GLuint in_prog_id,std::vector<std::string>* varrying_set)
{
  fbtf->set_shder_prog(in_prog_id);
  for(int i =0; i< varrying_set->size();i++)
  {
    fbtf->add_varying(varrying_set->at(i));
  }
  fbtf->config_varyings();
}
