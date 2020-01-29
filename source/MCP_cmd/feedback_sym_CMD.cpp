#include "feedback_sym_CMD.hpp"



     fbo_factory::operator() (fbo_type in_type,fbo_param_pak& in_fboppak)
     {
       switch (in_type)
          {
            case fbo_type::VIRTUAL :
            {

              break;
            }
            case fbo_type::FLOATING :
            {

              break;
            }

            case fbo_type::MULTI_TEXTURE :
            {

              break;
            }

            case fbo_type::MULTI_ATTACHMENT :

            {
              in_fboppak.attachments_buffs;
              glGenFramebuffer(GL_FRAMEBUFFER,)

              break;
            }

            case fbo_type::LAYERED :
            {

              break;
            }
          }
          if(in_type == fbo_type::MULTI_ATTACHMENT&fbo_type::MULTI_TEXTURE)
          {

          }
     }




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
