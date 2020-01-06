
#include "text_render.hpp"

#include FT_FREETYPE_H



void text_render_glyph::init(std::string in_text,std::string in_font, int size,
                           glm::vec4 in_colour,glm::vec2 in_pos, GLfloat scale )
{
  text= in_text;
  scale  = 1.0f;
  colour =in_colour;
  pos =   in_pos;
  //set_pos(in_pos);

  //glm::mat4 proj_matix = ;
  FT_Library fre_typ;

  std::cout << "\n\n##freetypelibsettupz\n";

  if(FT_Init_FreeType(&fre_typ))
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";

  FT_Face face;
  if(FT_New_Face(fre_typ,in_font.c_str(),0,&face))
  std::cerr << "ERROR::FREETYPE: Failed to load font\n";

  std::cout << "\n#newface\n";

  FT_Set_Pixel_Sizes(face,0,size);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for(GLubyte i = 0; i < 128; i++)
  {
    if(FT_Load_Char(face,i,FT_LOAD_RENDER))
    {std::cerr << "ERROR::FREETYTPE: Failed to load Glyph\n";
    continue;
    }

    //std::cout << "\n#texturework\n";
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


    //std::cout << "\n#load_chactor\n";

    character char_texture = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

    caracters_map.insert(std::pair<GLchar,character>(i,char_texture));
  }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
  	FT_Done_FreeType(fre_typ);

  //  confige vbaz
    std::cout << "\n#buffersetupz\n";
    glGenVertexArrays(1, &VAO_text);
	  glGenBuffers(1, &VBO_text);
    glBindVertexArray(VAO_text);

  	glBindBuffer(GL_ARRAY_BUFFER, VBO_text);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  	glEnableVertexAttribArray(loc_array[LOC_ATTRV_TEXT_INDEX]);
  	glVertexAttribPointer(loc_array[LOC_ATTRV_TEXT_INDEX], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

  	glBindBuffer(GL_ARRAY_BUFFER, 0);
  	glBindVertexArray(0);

}

void text_render_glyph::draw(gl_shader_t* shadr, int width, int height)
{
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glm::vec2 cursor_pos = pos;
  shadr->use_shader();
  glm::mat4 projection = glm::mat4(1.f);
   projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));

	glUniformMatrix4fv(loc_array[LOC_U_PROJ_INDEX], 1, GL_FALSE, glm::value_ptr(projection));
  glUniform4f(loc_array[LOC_U_COLOUR_INDEX],colour.r,colour.g,colour.b,colour.a);

  /// should be bound to paruaro texture unit. later array for diffrent fonts...
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(VAO_text);

  std::string::const_iterator s_const;

  for(s_const = text.begin(); s_const!= text.end();s_const++)
  {
    //std::cout << s_const;
    character r_char = caracters_map[*s_const];

    GLfloat xpos =  cursor_pos.x+r_char.baseline_glyph.x*scale;
    GLfloat ypos =  cursor_pos.y-(r_char.glyph_size.y-r_char.baseline_glyph.y) *scale;

    GLfloat width =r_char.glyph_size.x*scale;
    GLfloat hieght =r_char.glyph_size.y*scale;

    GLfloat vba_vertxz[6][4]
    {
      { xpos, ypos + hieght, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + width, ypos, 1.0, 1.0 },

			{ xpos, ypos + hieght, 0.0, 0.0 },
			{ xpos + width, ypos, 1.0, 1.0 },
			{ xpos + width, ypos + hieght, 1.0, 0.0 }
		};

    glBindTexture(GL_TEXTURE_2D,r_char.texture_ID);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_text);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vba_vertxz),vba_vertxz);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

    cursor_pos.x +=(r_char.next_glyph >> 6) * scale;
    }

  glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

}
