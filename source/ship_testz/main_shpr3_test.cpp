//#include "render_objk_cmd.hpp"
#include "opengl_utilityz.hpp"
#include "scene.hpp"


#include "lenz.hpp"

float delta_time = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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


    scene_struct scene_01;
    scene_01.init();

 /*
* gemomenty_lighting
*/

  gl_lightzctl test_lightz;


//light ambient
  glm::vec3 amb = glm::vec3(0.0,0.0,1.0);

  test_lightz.set_ambient(amb);

  light_propertyz lighttest;
  lighttest.phong_light.ambient = glm::vec3(0.0,0.0,1.0);
  lighttest.is_enabled = true;
  lighttest.position= glm::vec3(1.0,1.0,1.0);
  lighttest.intensity = glm::vec3(0.8,0.6,0.0);
  lighttest.Light_type = 1;
  GLuint lightA1_buffer_ID;


  //glBindBuffer(GL_SHADER_STORAGE_BUFFER,lightA1_buffer_ID);
//light diffuz
  glm::vec3 light_pos_d1(1.2f,1.0f,1.0f);
  glm::vec3 lcol_d1(0.8,0.0f,0.0f);

  float d_strgth = 3.f;

  //test_lightz.set_light_diffuse(light_pos_d1,lcol_d1,d_strgth);

//light point
  std::array<float,3> attun;
  attun[0]=4.f;
  attun[1]=3.f;
  attun[2]=2.f;
  glm::vec3 light_pos_ss2(1.2f,1.0f,1.0f);
  glm::vec3 lcol_ss2(0.0f,0.8f,0.0f);
  float drecional_strgth;
  //test_lightz.set_light_point(attun,light_pos_ss2,lcol_ss2,drecional_strgth);

  //light spot
  glm::vec3 light_pos_ss1(1.2f,1.0f,1.0f);
  glm::vec3 lcol_ss1(0.f,0.0f,0.8f);
  glm::vec3 cone_dir(1.f,1.f,1.f);
  float cos_cutoff =0.98;
  float exp =12;
  float catten = 3;


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

  //itunformz!

  std::array<GLuint,3> lightA1_uniform_array;

  GLuint mv_loc_light, mpv_loc_light,norm_mat_loc_light;
  GLuint v_poj_loc, view_loc, m_loc, m_v_p_basic;

   glm::mat4 model_matrix;

  //shader_3.use_shader();

  shader_3_basic->use_shader();
  //m_v_p_basic= glGetUniformLocation(shader_3_basic->program_ID,"model_view_projection");
  //shader_3_basic->add_uniform("model_view_projection",m_v_p_basic);
  //v_poj_loc= glGetUniformLocation(shader_3_basic->program_ID,"view_projection");
  //glUniformMatrix4fv(v_poj_loc,1,GL_FALSE,glm::value_ptr(view_projection));


  //glNamedBufferStorage( ,,GL_MAP_WRITE_BIT);
//glGetNamedBufferParameteriv( 	GLuint buffer,
//  	GLenum pname,
//  	GLint *params); GL_BUFFER_SIZE or GL_BUFFER_USAGE

/*
* SCENE setupz and load
*/
//scene scene_01;

scene_01.passthrough_lighting(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01,test_lightz);
scene_01.passthrough_lenz(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01,&prim_lenz);
scene_01.passthrough_lenz(Scene_Mesh_RDR::BASIC_SHADER_SCENE01,&prim_lenz);

/*
 *BUFFERZ MGMT CMDZ
*/

/*GL_MAP_COHERENT_BIT
//GL_MAP_PERSISTENT_BIT
//GL_SHADER_STORAGE_BUFFER
//GL_MAP_INVALIDATE_RANGE_BIT
//GL_MAP_UNSYNCHRONIZED_BIT
//GL_MAP_READ_BIT
glNamedBufferSubData(	GLuint buffer,
  //glNamedBufferData
	GLintptr offset,
	GLsizei size,
	const void *data);
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


 shader_lightA01->use_shader();
 glCreateBuffers(1, &lightA1_buffer_ID);

 //glNamedBufferStorage(lightA1_buffer_ID, sizeof(sbt), NULL, GL_DYNAMIC_STORAGE_BIT);
 //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, lightA1_buffer_ID);
//glBufferSubData()

offset_table off_table;
//glNamedBufferSubData(lightA1_buffer_ID,0,sizeof(glm::vec3),&sbt.ambent_test);

  std::cout <<"#####entering main loop setup compleate;\n \n";


  while(!glfwWindowShouldClose(glfw_window))
  {
    //process keyz
    float currentFrame = glfwGetTime();
    delta_time = currentFrame - lastFrame;
    lastFrame = currentFrame;
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

    test_ajustship.rotation_ajust.y =0.09f;
    test_ajustship2.posz_ajust.x=-0.001f;
    //test_ajustship2.rotation_ajust.y=-0.01f;
    //test_ajustship2.posz_ajust.x = -0.08f;
    //shipA3.update_mesh_model(test_ajustship);
    ship_basic.update_mesh_model(test_ajustship2);


  /*
  * DRAW CALLZ
  */


    scene_01.draw_scene(Scene_Mesh_RDR::LIGHT_PROG01_SCENE01);
    scene_01.draw_scene(Scene_Mesh_RDR::BASIC_SHADER_SCENE01);

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
          prim_lenz.lenz_move(delta_time,'w');
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(delta_time,'s');
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(delta_time,'a');
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
          prim_lenz.lenz_move(delta_time,'d');
        }
      }
