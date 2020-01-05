//#include "render_objk_cmd.hpp"
#include "basez/opengl_utilityz.hpp"
#include "basez/shader_parser.hpp"
//#include "assimp_scene_loader.hpp"
#include "basez/lenz.hpp"

#include "animation.hpp"
#include "skeleton.hpp"
#include "animated_mesh.hpp"
namespace globalz
{
std::unordered_map<std::string,gl_shader_t*> shader_map;
std::unordered_map<std::string,gl_shader_t*>::iterator shader_iter;
}

void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool is_cursor_captured = false;
//lenz at global to allow mouse/keybord callback. put into some kindamap.
view_lenz prim_lenz;

/*
* MAIN!
*/

  int main(int argc, char* argv[])
  {
  /*
  GLM AND OPENGL AND GLFW inailzaiton
  */
    int errocode;
    GLFWwindow* glfw_window;

    std::cout << "launching Main Window\n";
    errocode = opengl_context_settup();

    std::cout << "###openglcontexcode::"<< errocode <<'\n';

    glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_toolGlfz",NULL,NULL);
    glfwSetCursorPosCallback(glfw_window, mouse_callback);
    glfwSetScrollCallback(glfw_window, scroll_callback);

// tell GLFW to capture our mouse

    errocode = run_opengl_setup(glfw_window);
    std::cout << "\n ###openglsetupcode::"<< errocode;

      gl_shader_t* shader_animA= new gl_shader_t();

      int errcode = run_parse();
      std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();
      std::vector<int> shdr_amin_list;
      //shader_setupz
      bool is_complie = true;
      std::cout <<"number of shaderz" << shader_TV_ptr->size();

      shader_animA->setup_shader_code(shader_TV_ptr->at(1));
      shader_animA->setup_shader_code(shader_TV_ptr->at(0));
      shdr_amin_list.push_back(SHD_ANIM_VERTEX);
      shdr_amin_list.push_back(SHD_AMIN_FRAG);

      is_complie =shader_animA->create_link_program(shdr_amin_list);
      shader_animA->test_flags();

    std::cout << "##SHADER settup COMPLEATE\n";
    if(is_complie == false)
    {
      exit(-1);
    }


 /*
* gemomenty_lighting
*/

  /*
  *LENZ SETUP>>>deal with it being gobalz?
  */

  std::cout << "load_lenz\n";

  glm::vec3 world_up(0.f,1.f,0.f);
  glm::vec3 lenz_front(0.f,0.f,-1.f);
  glm::vec3 lenz_pos(0.f,0.f,1.f);
  float fov= 90.f;
  float near_plane = 0.1f;
  float far_plane = 1000.f;
  float lenz_radius = 10.0f;

  /*
  *MATRIX INILAZATION SETZ
  */
  glm::mat4  view_projection =glm::mat4(1.f);
  glm::mat4 view_matrix(1.f);
  glm::mat4 Projection(1.f);

  view_matrix =  prim_lenz.return_lenz_view();
  Projection  = prim_lenz.lenz_projection();
  view_projection = Projection*view_matrix;

  /*
  * UNIFORM SETTUPzzz.
  */

   glm::mat4 model_matrix;


/*
 *BUFFERZ MGMT CMDZ
*/
/*
* GOBAL OPEN GL ENABLEZ
*/
GLint frame_buf_width,frame_buf_hight;

 glEnable(GL_DEPTH_TEST);
 glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

 /*
 Mainloopz!
 */

  std::cout <<"#####entering main loop setup compleate;\n \n";


  while(!glfwWindowShouldClose(glfw_window))
  {
    //process keyz
    float currentFrame = glfwGetTime();
    globalz::delta_time = currentFrame - globalz::lastFrame;
    globalz::lastFrame = currentFrame;
    process_input_glfw(glfw_window);

    /*
    BEGIN RENDER CYCLE! OHHH
    */
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //set projectionz
    glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

    view_matrix =  prim_lenz.return_lenz_view();
    Projection  = prim_lenz.lenz_projection();

    view_projection = glm::mat4(1.f);
    view_projection = Projection*view_matrix;

    /*
    * MODEL TRANFORMZ
    */



  /*
  * DRAW CALLZ
  */


      glfwSwapBuffers(glfw_window);

      //[postopz]
      //and poll glfw
      glfwPollEvents();
/*
      if(screen_beenresized ==true)
      {
        prim_lenz.update_aspec_ratio(frame_buf_width,frame_buf_hight);
        screen_beenresized = false;
      }*/

    }//endmain loop
/*
* CLEANUP GOES HERE
*/


  return 0;
      }

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
        prim_lenz.process_mouse(xoffset,yoffset);
      }

      void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
      {
        prim_lenz.process_scroll(yoffset);
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


        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(globalz::delta_time,'w');
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(globalz::delta_time,'s');
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(globalz::delta_time,'a');
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(globalz::delta_time,'d');
        }
      }
