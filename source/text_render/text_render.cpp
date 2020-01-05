
#include "text_render.hpp"

#include FT_FREETYPE_H

text_render_gui::text_render_gui(std::string in_text,std::string in_font, int size, glm::vec4 in_colour,glm::vec2 in_pos)
{
  text= in_text;
  scale  = 1.0f;
  colour =in_colour;

  set_pos(in_pos);

  //glm::mat4 proj_matix = ;
  FT_Library fre_typ;

  if(FT_Init_FreeType(&fre_typ))
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";

  FT_Face face;
  if(FT_New_Face(fre_typ,in_font.c_str(),0,&face))
  std::cerr << "ERROR::FREETYPE: Failed to load font\n";

  FT_Set_Pixel_Sizes(face,0,size);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for(GLubyte i = 0; i < 128; i++)
  {
    if(FT_Load_Char(face,i,FT_LOAD_RENDER))
    {std::cerr << "ERROR::FREETYTPE: Failed to load Glyph\n";
    continue;
    }

    GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    character char_texture = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

    caracters_map.insert(std::pair<GLchar,character>(i,char_texture));
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
  	FT_Done_FreeType(fre_typ);

    //confige vbaz

    glGenVertexArrays(1, &text_VAO);
	  glGenBuffers(1, &text_VBO);
    glBindVertexArray(text_VAO);

  	glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  	glEnableVertexAttribArray(loc_array[LOC_U_TEXT_INDEX]);
  	glVertexAttribPointer(loc_array[LOC_U_TEXT_INDEX], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

  	glBindBuffer(GL_ARRAY_BUFFER, 0);
  	glBindVertexArray(0);

  }

}

void text_render_gui::draw(gl_shader* shadr, glm::mat4& in_proj_matrix)
{
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  shadr->use_shader();
  //glUniform3f()
}
