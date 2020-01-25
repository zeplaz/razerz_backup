
#include "../basez/opengl_utilityz.hpp"

#include "partical_env.hpp"
#include "../MCP_cmd/feedback_sym.hpp"

#include "../basez/3rdparty/frame_to_video.hpp"

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

//opencv capture to AVI REQUERD CALLBACKS
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);

//auto prt_set_pramz = std::mem_fn(&multiframe_capturer::set_paramz); (multiframe_capturer::set_paramz)
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

  gl_shader_t* shader_compute =  new  gl_shader_t();
  gl_shader_t* shad_partc_viz = new  gl_shader_t();
  int errcode = run_parse();

  //shader datastucz
  std::map<unsigned int,shader_tuple_type*>* shder_tup_map =  return_shdrmap_ptr_TV();

  std::vector<int> shad_comp_list;
  std::vector<int> shad_partic_viz_list;
  bool is_complie = true;


  std::cout <<"number of shaders in list " << shder_tup_map->size();

    //partical compue sym shadrers
  shader_compute->setup_shader_code(shder_tup_map->at(SHD_PARTIC_A_COMPUTE));
  shad_comp_list.push_back(SHD_PARTIC_A_COMPUTE);

  is_complie = shader_compute->create_link_program(shad_comp_list);
  shader_compute->test_flags();

  if(is_complie == false)
  {
    std::cerr <<"ERROR compute COMPLIE FAILD\n";
    exit(-1);
  }

  shad_partc_viz->setup_shader_code(shder_tup_map->at(SHD_PARTIC_VIZ_VERTEX));
  shad_partc_viz->setup_shader_code(shder_tup_map->at(SHD_PARTIC_VIZ_FRAG));
  shad_partic_viz_list.push_back(SHD_PARTIC_VIZ_VERTEX);
  shad_partic_viz_list.push_back(SHD_PARTIC_VIZ_FRAG);

  is_complie = shad_partc_viz->create_link_program(shad_partic_viz_list);
  shad_partc_viz->test_flags();

  //END SHADERS FOR COMPUTER PARTICALS


  if(is_complie == false)
  {
    std::cerr <<"ERROR partical visualz COMPLIE FAILD\n";
    exit(-1);
  }

  std::cout << "##SHADER settup COMPLEATE\n";

  comput_partic_sim comp_part_fire;

  comp_part_fire.set_renderz_ID(shader_compute,shad_partc_viz);
  comp_part_fire.set_lenz(prim_lenz);
  glm::vec4 tst_orgin = glm::vec4(-100.5,10.4,-100.4,1);
  comp_part_fire.set_orgin(tst_orgin);
  comp_part_fire.init();

  glClearColor(0.2f, 0.0f, 0.1f, 1.0f);


  multiframe_capturer mf_c;
  vid_cap_callback = &multiframe_capturer::set_paramz;
  //vid_cap_callback(mf_c,);//&;
//  mf_c.set_paramz(glfw_window,250);

  std::cout <<"#####entering main loop setup compleate;\n \n";

  while(!glfwWindowShouldClose(glfw_window))
  {
    //process keyz
    float currentFrame = glfwGetTime();
    delta_time = currentFrame - lastFrame;
    lastFrame = currentFrame;
    process_input_glfw(glfw_window);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    comp_part_fire.partical_dispaly();

    //set projectionz
    glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

    glfwSwapBuffers(glfw_window);
    if(take_frame_video == true)
    { bool compleate;

      mf_c.export_framebuff_avi(&compleate);
      if(compleate ==true)
      {
        take_frame_video = false;
      }
    }

    glfwPollEvents();
    std::cout<< "orgianlorgia::" << '\n'


    << tst_orgin.x << '\n'
    << tst_orgin.y << '\n'
    << tst_orgin.z << '\n';
    std::cout << "\nsomefunz::\n"
    << pow(delta_time,tan(tst_orgin.x)) <<'\n'
    << pow(tan(delta_time*delta_time)*sin(delta_time),sin(delta_time))*tan(tst_orgin.x)<<'\n'
    << tan(tst_orgin.y)/sin(tst_orgin.y)<<'\n';

    tst_orgin.x+= pow(tan(delta_time*delta_time)*sin(delta_time),sin(delta_time))*tan(tst_orgin.x);
    tst_orgin.y+= tan(tst_orgin.y)/sin(tst_orgin.y)*delta_time;
    tst_orgin.z-=((tan(tst_orgin.z)/sin(tst_orgin.z)))*delta_time;
    if(tst_orgin.x>138||tst_orgin.x<-138)
    {
      tst_orgin.x = 1;
    }
    if(tst_orgin.z>176||tst_orgin.z<-1148)
    {
      tst_orgin.z = 1;
    }
    if(tst_orgin.y>138||tst_orgin.y<-138)
    {
      tst_orgin.y = 1;
    }

    std::cout<< "modfied::" << '\n'
    << tst_orgin.x << '\n'
    << tst_orgin.y << '\n'
    << tst_orgin.z << '\n';
    comp_part_fire.set_orgin(tst_orgin);

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

  if(glfwGetKey(window,GLFW_KEY_F2) ==  GLFW_PRESS)
  {
    capture_frame_buff_avi(window,vid_cap_callback);
    take_frame_video=true;
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
