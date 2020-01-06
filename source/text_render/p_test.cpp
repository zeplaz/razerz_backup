

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
  std::cout << "\n ###openglsetupcode::"<< errocode;

  gl_shader_t* shader_glyph= new gl_shader_t();

  int errcode = run_parse();

  //shader datastucz
  std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();
  std::vector<int> shdr_glyph_list;


  //shader_setupz
  bool is_complie = true;
  std::cout <<"number of shaders in list " << shader_TV_ptr->size();
  shader_glyph->setup_shader_code(shader_TV_ptr->at(2));
  shader_glyph->setup_shader_code(shader_TV_ptr->at(3));
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

    GLint frame_buf_width,frame_buf_hight;

     //glEnable(GL_DEPTH_TEST);
     glClearColor(0.2f, 0.0f, 0.1f, 1.0f);



  //character c;
  text_render_glyph glphy_render;
  glphy_render.get_shader_loc(shader_glyph);

//testfpmt
  std::string thetext = " some text_test";
  std::string curr_font=  "fonts/CODE3X.ttf";
  glm::vec4 font_colour = glm::vec4(0.2f,0.8f,0.3f,1.0f);
  int size_64 = 64;
  glm::vec2 text_pos = glm::vec2(320.0f, 500.0f);
    GLfloat scale = 1.f;

  glphy_render.init(thetext,curr_font,size_64,font_colour,text_pos,scale);


  text_render_glyph glphy_render2;
  glphy_render2.get_shader_loc(shader_glyph);

//testfpmt
  std::string thetext2 = " THEOTHERTEXT";
  std::string curr_font2=  "fonts/CODE3X.ttf";
  glm::vec4 font_colour2 = glm::vec4(0.2f,0.8f,0.3f,1.0f);
  int size_642 = 64;
  glm::vec2 text_pos2 = glm::vec2(120.0f, 600.0f);
  GLfloat scale2 = 1.f;

  glphy_render2.init(thetext2,curr_font2,size_642,font_colour2,text_pos2,scale);


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


    glphy_render.draw(shader_glyph,frame_buf_width,frame_buf_hight);
    glphy_render2.draw(shader_glyph,frame_buf_width,frame_buf_hight);

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
