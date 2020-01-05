//texture.cpp
#include "texture.hpp"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb_image.h"

GLenum Texture_gl::return_TextureFormat(Format formate)
{
  switch (formate)
   {
      case Format::Format_Grayscale: return GL_LUMINANCE;
      case Format::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
      case Format::Format_RGB: return GL_RGB;
      case Format::Format_RGBA: return GL_RGBA;
      case Format::Format_RGBA8: return GL_RGBA8;
      case Format::Format_RGB8: return GL_RGB8;
      default: throw std::runtime_error("Unrecognised Bitmap::Format");
  }
}

void Texture_gl::init_texture()
{
  glActiveTexture(GL_TEXTURE0+texture_indexUnit);
  glBindTexture(GL_TEXTURE_2D,texture_ID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, return_TextureFormat(formate_internal), width,
              height, 0,return_TextureFormat(formate_external), GL_UNSIGNED_BYTE, image);
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D,0);
}

void Texture_gl::load_texture(std::string path,int force_channel,int text_unitindex)
{
  std::cout <<"stbi_begin\n";
  image = stbi_load(path.c_str(),&width,&height,&n,force_channel);
  std::cout <<"stbi_loadcompleate\n";
  set_texture_unit_index(text_unitindex);
}

void Texture_gl::set_min_Mag_Filter(Filter filt,char min_mag)
  {
    switch (filt)
    {
      case Filter::LINEAR :
      {
       if(min_mag == 'i')
       minFiler = GL_LINEAR;
       if(min_mag == 'a')
       magFiler = GL_LINEAR;
       break;
      }
      case Filter::NEAREST :
      {
        if(min_mag == 'i')
        minFiler = GL_NEAREST;
        if(min_mag == 'a')
        magFiler = GL_NEAREST;
        break;
      }
      case Filter::MIPMAP :
      {
        if(min_mag == 'i')
        minFiler = GL_MIPMAP;
        if(min_mag == 'a')
        magFiler = GL_MIPMAP;
        break;
      }

      default : throw std::runtime_error("Unrecognised Bitmap::Filter");
    }
  }
