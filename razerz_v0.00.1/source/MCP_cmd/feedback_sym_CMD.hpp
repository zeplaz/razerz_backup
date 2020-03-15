#pragma once

#include "../basez/gl_lib_z.hpp"
#include "mcp_lib.hpp"

#include <utility>
#include <type_traits>
#include <unordered_map>
#include <map>

struct fbo_param_pak
{

};

class framebuffer_objk : public sym_object
{
    protected :
    std::multimap<FBO_types,GLuint>> rawfbo_map;
    public :


     void create_virtual()
     {
       //reqyest from the frambuf factory. a new wraperobject, andplace in map.
       fbo_type = FBO_type::VIRTUAL;
       GLuint fbo;
       glGenFramebuffer(1,&fbo);
       rawfbo_map.insert(fbo_type,fbo);
       if(out_fbo !=nullptr)
       {
         return fbo;
       }
       else return nullptr;

     }
     void configure(fbo_param_pak in_ppak)
     {

     }


 void create_floating(bo_param_pak in_ppak)
 {
   GLuint texture;
   fbo_type = FBO_type::FLOATING;
   GLuint fbo;
   glGenFramebuffer(1,&fbo);

   glTextureStorage2D(texture,1,GL_RGBA32F,in_ppak.width,in_ppak.hight);

 }


     void copy_frambufz(GLint width, GLint hight, GLuint read_buff,GLuint draw_buff,
                        int n, std::vector<GLeum> attach_list,
                        std::vector<std::pair<GLenum,GLenum>>* in_attach_pair,
                        float scale,GLenum in_buff_type)
     {
       glBindFramebuffer(GL_DRAW_FRAMEBUFFER,draw_buff);
       glBindFramebuffer(GL_READ_FRAMEBUFFER,read_buff);


       glDrawBuffers(n,attach_list->data());
       for(int i = 0; i< in_attach.size();i++)
       {
         glReadBuffers(in_attach->.at(i));
         glBlitFrameBuffer(0,0,width,hight,width*scale,hight*scale,width,hight,in_buff_type,GL_LINEAR);
       }


     }
     void copy_to_texture()
     {

     }

};

class fbo_factory
{
    public :
    std::shared_ptr<framebuffer_objk> operator () (fbo_type in_type, fbo_param_pak& in_fboppak);

};

class texture_factory
{
  public :
  GLuint operator () (texture_param_pak& in_tppak);
};

class framebuffer_control

{
  private :
  //int fbc_ID;
  //GLuint std::unordered_map<int,framebuffer_objk> fbo_map;
  std::unordered_map<int,std::shared_ptr<framebuffer_objk>> framebo_map;
  std::unordered_map<int,GLuint> framebz_textures_map;

  fbo_factory factory_fbo;
  texture_factory factory_texture;


  public  :

    void create_fbo(fbo_type in_type, fbo_param_pak& in_ppak)
    {
     std::shared_ptr<framebuffer_objk> temp_ptr =factory_fbo(in_type);
     framebo_map.insert(std::make_pair(temp_ptr->obj_ID,temp_ptr));
    }

  //  glCreateFramebuffers(n,GLuint * etc)

    GLuint created_new_texture()
    {
      factory_texture();
      
      glGenTexture()
      glCreateTextires();
    }
    void fbo_to_texture()
    {
      //attach= GL_COLOR_ATTACHMENTi? GL_DEPTH_ATTACHMENT,GL_STENCIL_ATTCHMENT,orcomind

      glNamedFrameBufferTexture(fbo,attch,text,level);
      glNamedFrameBufferTextureLayer(fbo,attach,text,level,layer);
    }


    bind()
    {
      //GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER, GL_FRAMEBUFFER
      //glBindFramebuffer(target,GLUINT.)
    }


  void setup_render_buffer()
  {
    glCreateRenderbuffers(n,GLuint * etc)

  //if depth GL_DEPTH_COMPONENT
  }

};



class feedbacktransform
{
  private :
  int fbt_ID;
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
