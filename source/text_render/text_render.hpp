#pragma once


/*
Metierals and soruce from sb7 ::https://github.com/openglsuperbible/sb7code
and # CPP-Game-Development-By-Example::https://www.packtpub.com/web-development/c-game-development-example?utm_source=github&utm_medium=repository&utm_campaign

*/


#include "../basez/gl_lib_z.hpp"
#include "../basez/shader_pipeline_CMD.hpp"
#include "../basez/shader_parser.hpp"

#include <map>
#include <string>
#include <iostream>


#include <ft2build.h>
//#include "../basez/3rdparty/ft2build.h"
constexpr auto LOCAION_ARRAY_SIZE = 4;

constexpr auto LOC_ATTRV_TEXT_INDEX =0;
constexpr auto LOC_U_TEXT_INDEX =1;
constexpr auto LOC_U_COLOUR_INDEX =2;
constexpr auto LOC_U_PROJ_INDEX = 3;

struct character {
  GLuint     texture_ID;  // Texture ID of each glyph texture
	glm::ivec2 glyph_size;       // glyph Size
	glm::ivec2 baseline_glyph;    // baseline to left/top of glyph
	GLuint     next_glyph;    // id to next glyph
};

class text_render_glyph {
  private :
  std::string text;
  GLfloat scale;
  glm::vec4 colour;
  glm::vec2 pos;

  GLuint VAO_text, VBO_text;
  std::map<GLchar,character> caracters_map;

  std::array<GLuint,LOCAION_ARRAY_SIZE> loc_array;
  gl_shader_t* current_shader;


  public :

  //text_render_glyph(std::string in_text,std::string in_font, int size, glm::vec4 in_colour, glm::vec2 in_pos);
  void init(std::string in_text,std::string in_font, int size,
    glm::vec4 in_colour, glm::vec2 in_pos, GLfloat in_scale);

  void  draw(gl_shader_t* shadr, int width, int height);

  inline void set_pos(glm::vec2 in_pos)
  {
    pos = in_pos;
  }
  inline void set_text( std::string in_text)
  {
    text = in_text;
  }

  inline void set_colour( glm::vec4 in_colour)
  {
    colour = in_colour;
  }


inline void get_shader_loc(gl_shader_t* shadr)
{
  //shadr->use_shader();
  loc_array[LOC_U_TEXT_INDEX] = glGetUniformLocation(shadr->program_ID,"utext_samp");
  loc_array[LOC_U_COLOUR_INDEX] = glGetUniformLocation(shadr->program_ID,"ucolour");
  loc_array[LOC_U_PROJ_INDEX] = glGetUniformLocation(shadr->program_ID,"proj");

  loc_array[LOC_ATTRV_TEXT_INDEX] = glGetAttribLocation(shadr->program_ID,"vertex_pos_tex");


}

inline void set_shader(gl_shader_t* shdr)
{
  current_shader = shdr;
  this->get_shader_loc(current_shader);
}

};


class text_overlay{

  private :

  gl_shader_t* shadr;
  GLuint text_buff;
  GLuint font_texture;
  GLuint VAO_textover;

  char* screen_buff;
  int buff_height;
  int buff_width;
  bool need_update;
  int cursor_x;
  int cursor_y;


  public :
  void init();

  void draw();
  inline void set_shader(gl_shader_t* in_shd)
  {
    shadr=in_shd;
  }


  void update_text(const char* in_string, int x,int y);
  void shutdown();
  void clear();

  void scroll(int linez);
  inline void move_cursor(int x, int y)
  {
     cursor_x=x;
     cursor_y=y;
  }




};
