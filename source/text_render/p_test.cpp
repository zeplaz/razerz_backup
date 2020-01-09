

#include "text_render.hpp"
#include "../basez/3rdparty/sb7ktx.h"
#include "../basez/opengl_utilityz.hpp"
#include "../basez/lenz.hpp"


float delta_time = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool is_cursor_captured = false;
GLint frame_buf_width,frame_buf_hight;


view_lenz* prim_lenz =nullptr;


/*
* MAIN!
*/

int main(int argc, char* argv[])
{

  int errocode;
  GLFWwindow* glfw_window;

  std::cout << "launching Main Window\n";
  errocode = opengl_context_settup();

  std::cout << "###openglcontexcode::"<< errocode <<'\n';
  prim_lenz = new view_lenz();

  glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_tooltext_teser",NULL,NULL);
  glfwSetCursorPosCallback(glfw_window,mouse_callback);
  glfwSetScrollCallback(glfw_window, scroll_callback);

  errocode = run_opengl_setup(glfw_window);
  std::cout << "\n ###openglsetupcode::"<< errocode << "\n";

  gl_shader_t* shader_glyph= new gl_shader_t();

  int errcode = run_parse();

  //shader datastucz
  std::map<unsigned int,shader_tuple_type*>* shder_tup_map =  return_shdrmap_ptr_TV();

  //std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();
  std::vector<int> shdr_glyph_list;


  //shader_setupz
  bool is_complie = true;
  std::cout <<"number of shaders in list " << shder_tup_map->size();
  shader_glyph->setup_shader_code(shder_tup_map->at(SHD_GLYPH1_VERTEX));
  shader_glyph->setup_shader_code(shder_tup_map->at(SHD_GLYPH1_FRAG));
  shdr_glyph_list.push_back(SHD_GLYPH1_VERTEX);
  shdr_glyph_list.push_back(SHD_GLYPH1_FRAG);

  shader_glyph->create_link_program(shdr_glyph_list);
  shader_glyph->test_flags();


  if(is_complie == false)
  {
    std::cerr <<"ERROR SHADER COMPLIE FAILD\n";
    exit(-1);
  }

  std::cout << "##SHADER settup COMPLEATE\n";


    glm::mat4 Projection(1.f);
    Projection  = prim_lenz->lenz_projection();



     //glEnable(GL_DEPTH_TEST);
     glClearColor(0.2f, 0.0f, 0.1f, 1.0f);


//ngarkimit
//textrebders
  text_render_glyph glphy_render_Maranallo;
  glphy_render_Maranallo.get_shader_loc(shader_glyph);

//testfpmt
  std::string thetext = " some text_test";
  std::string curr_font=  "fonts/Maranallo.ttf";
  glm::vec4 font_colour = glm::vec4(0.4f,0.3f,0.6f,1.0f);
  int size_64 = 64;
  glm::vec2 text_pos = glm::vec2(320.0f, 500.0f);
    GLfloat scale = 1.0f;

  glphy_render_Maranallo.init(thetext,curr_font,size_64,font_colour,text_pos,scale);


  text_render_glyph glphy_render_CR;
  glphy_render_CR.get_shader_loc(shader_glyph);

//testfpmt
  std::string thetext2 = " THEOTHERTEXT";
  std::string curr_font2=  "fonts/Cocktail_Regular.ttf";
  glm::vec4 font_colour2 = glm::vec4(0.3f,0.6f,0.4f,1.0f);
  int size_642 = 64;
  glm::vec2 text_pos2 = glm::vec2(122.0f, 604.0f);
  GLfloat scale2 = 1.0f;

  glphy_render_CR.init(thetext2,curr_font2,size_642,font_colour2,text_pos2,scale);


  text_render_glyph org_splash;
  org_splash.get_shader_loc(shader_glyph);

//testfpmt
  std::string org_splash_thetext = "ORGBURO_CMD_z";
  std::string org_splash_curr_font=  "fonts/CODE3X.ttf";
  glm::vec4   org_splash_colour = glm::vec4(0.2f,0.8f,0.3f,1.0f);
  int org_splash_size_64 = 64;
  glm::vec2 org_splash_text_pos = glm::vec2(407.0f, 403.0f);
  GLfloat org_splash_scale = 1.2f;

  org_splash.init(org_splash_thetext,org_splash_curr_font,org_splash_size_64,org_splash_colour,org_splash_text_pos,org_splash_scale);


    std::cout <<"#####entering main loop setup compleate;\n \n";

  while(!glfwWindowShouldClose(glfw_window))
  {
    //process keyz
    float currentFrame = glfwGetTime();
    delta_time = currentFrame - lastFrame;
    lastFrame = currentFrame;
    process_input_glfw(glfw_window);

    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //set projectionz
    glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);
    //Projection  = prim_lenz->lenz_projection();


    glphy_render_Maranallo.draw(shader_glyph,frame_buf_width,frame_buf_hight);
    glphy_render_CR.draw(shader_glyph,frame_buf_width,frame_buf_hight);
    org_splash.draw(shader_glyph,frame_buf_width,frame_buf_hight);
    glfwSwapBuffers(glfw_window);

    glfwPollEvents();

    }


  return 0;
}




///boilplate move to utilitiz
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY= ypos;
    firstMouse = false;
  }
  float xoffset = xpos- lastX;
  float yoffset = lastY-ypos;
  lastX=xpos;
  lastY=ypos;
  prim_lenz->process_mouse(xoffset,yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  prim_lenz->process_scroll(yoffset);
}

void process_input_glfw(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {glfwSetWindowShouldClose(window, true);}

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
          {
            if(is_cursor_captured)
            {
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
              is_cursor_captured=false;
            }
            else
            {
              is_cursor_captured= true;
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            }
//  float lenz_speed = 2.5*delta_time;
  if(glfwGetKey(window,GLFW_KEY_F1) ==  GLFW_PRESS)
  {
    take_screenshot_to_file(frame_buf_width,frame_buf_hight);
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'w');
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'s');
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'a');
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'d');
  }
}
