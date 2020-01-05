#pragma once

#include "../basez/gl_lib_z.hpp"
#include "../basez/shader_parser.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
//#include <glm.hpp> // glm::mat4

#include <glm/glm.hpp> // glm::mat4
#include <glm/ext.hpp> // perspective, translate, rotate

#include <map>
#include <string>
#include <iostream>


#include <ft2build.h>


constexpr auto LOC_ATTRV_TEXT_INDEX =0;
constexpr auto LOC_U_TEXT_INDEX =1;
constexpr auto LOC_U_COLOUR_INDEX =2;

struct character {
  GLuint     texture_ID;  // Texture ID of each glyph texture
	glm::ivec2 glyph_size;       // glyph Size
	glm::ivec2 baseline_glyph;    // baseline to left/top of glyph
	GLuint     next_ID;    // id to next glyph
};

class text_render_gui {
  private :
  std::string text;
  GLfloat scale;
  glm::vec4 colour;
  glm::vec2 pos;

  GLuint text_VAO, text_VBO;
  std::map<GLchar,character> caracters_map;

  std::array<GLuint,3> loc_array;
  gl_shader_t* current_shader;


  public :

  text_render_gui(std::string in_text,std::string in_font, int size, glm::vec4 in_colour, glm::vec2 in_pos);

  void  draw(gl_shader* shadr, glm::mat4& in_proj_matrix);

  inline void set_pos(glm::vec2 in_pos)
  {
    pos = in_pos;
  }
  inline void set_text( std::string in_text)
  {
    text = in_text;
  }



inline void get_shader_loc(gl_shader_t* shadr)
{
  //shadr->use_shader();
  loc_array[LOC_U_TEXT_INDEX] = glGetUniformLocation(shadr->program_ID,"utext_samp");
  loc_array[LOC_U_COLOUR_INDEX] = glGetUniformLocation(shadr->program_ID,"ucolour");
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
  GLuint text_buff;
  GLuint font_texture;
  GLuint VOA_textover;

  char* screen_buff;
  int buff_hight;
  int buff_width;
  bool need_update;
  int cursor_x;
  int cursor_y;


  public :

  void move_cursor(int x, int y);
  
};
