#include "geometry.hpp"
#include "pre_comb_objz.hpp"
#include "render_objk_cmd.hpp"

   void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam)
{
     //ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}


void process_input_glfw(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

}

void gl_run_render(GLFWwindow* glfwwindow, std::vector<gl_shader_t*>& in_shaderz,
                   std::vector<std::vector<GLuint>>& vetex_array_objkz)
{
  //std::cout <<"\n ###nummof shaders to process" << in_shaderz.size() << "  num of objket packagez::" << vetex_array_objkz.size() << '\n' << '\n';
float timeValue = glfwGetTime();
float sin_green = sin(timeValue);
float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);

for (size_t i =0; i<in_shaderz.size();i++)
{
  in_shaderz.at(i)->use_shader();
  int vertexColorLocation = glGetUniformLocation(in_shaderz.at(i)->program_ID, "ourColor");
  //std::cout << "vertex_colour_unform at::" << vertexColorLocation << "  Progamid::"
        //    << in_shaderz.at(i)->program_ID << "ourColor" << '\n';
  std::vector<GLuint> vao_vec  =  vetex_array_objkz.at(i);
  glUniform4f(vertexColorLocation, sin_tsnz, sin_green, colour_angluretime, 1.f);

  for(size_t k=0; k<vao_vec.size();k++)
  {
   //std::cout << "binding:voa:" << vao_vec.at(k) << '\n';
   if(k==1)
   {
     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   }
   else {
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
   }
   glBindVertexArray(vao_vec.at(k));
  // glDrawArrays(GL_TRIANGLES, 0, 12*3);
  }
  }
  }
/*
* MAIN!
*/
  int main(int argc, char* argv[])
  {
  /*
  GLM AND OPENGL AND GLFW inailzaiton
  */

    GLFWwindow * glfw_window;
    glewExperimental = GL_TRUE;
    //launch gluitInit
    if (!glfwInit())
  {
    std::cout << "flfwinit faild :()\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  std::cout << "launching Main Window\n";

  glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_toolGlfz",NULL,NULL);
  if(!glfw_window)
  {
    glfwTerminate();
    std::cout <<"windowfailureload\n";
    return -3;
  }

  glfwMakeContextCurrent(glfw_window);
  glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

  GLenum glewErr = glewInit();
  std::cout << "glew_code::" << glewErr <<'\n' <<'\n';
  glViewport( 0, 0, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HIGHT );
GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
{
  std::cout <<"debug iniaizled\n";
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

  /*
  * SHADER SETUPZ
  */
  gl_shader_t shader_3;

  int errcode = run_parse();
  shader_3.test_flags();
  std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();

  shader_3.setup_shader_code(shader_TV_ptr->at(0));
  shader_3.setup_shader_code(shader_TV_ptr->at(1));
  std::vector<int> base_shader_idz;
  base_shader_idz.push_back(6);
  base_shader_idz.push_back(5);
  shader_3.create_link_program(base_shader_idz);
  shader_3.test_flags();

  std::vector<gl_shader_t*> shader_prt_vec;
  shader_prt_vec.push_back(&shader_3);

  /*
  working DATA for current test.
  */
    model_ajustment test_ajustship;
    model_ajustment test_ajustship2;

    model_ajustment ship_2_orgin;
    ship_2_orgin.posz_ajust.x=0.9f;
    ship_2_orgin.posz_ajust.y=0.5f;
    ship_2_orgin.posz_ajust.z= -0.1f;
    ship_2_orgin.scale_ajust = glm::vec3(0.1f);
    ship_2_orgin.rotation_ajust.y = 120.f;

    /*
     *BUFFERZ MGMT CMDZ
    */
    //std::vector<GLuint> buffarry_obk_vec_01;
  //  std::vector<std::vector<GLuint>> encaple_vaoz;
    //encaple_vaoz.push_back(buffarry_obk_vec_01);

  /*
  *meshsettup and gemomenty_lighting
  */
  std::cout <<"setupmeshz \n";
  wavefornt_parser2 wp2;

  std::string ship_res_textA2 = {"data_extrn/boat_Base_2.obj"};
  std::pair<std::vector<mesh_vertex>*,std::vector<unsigned int>*> test_mesh_vec  = wp2.read_file(ship_res_textA2);

  mesh test_mesh;
  //test_mesh.init(&wp2,ship_res_textA2);
  test_mesh.init(test_mesh_vec,M_Model_Flag::MODEL_UNIFORM);
  test_mesh.bindmesh_buf();

  //test_mesh.flag_ORer(M_Tex_Flag::TEXTYR_BASIC);
  mesh test_mesh2;
  //test_mesh2.init(&wp2,ship_res_textA2);
  test_mesh2.init(test_mesh_vec,M_Model_Flag::MODEL_UNIFORM);
  test_mesh2.bindmesh_buf();
  test_mesh2.set_mesh_model_origin(ship_2_orgin);


  glm::vec3 lpos(1.2f,1.0f,2.0f);
  glm::vec3 lcol(0.6f,0.2f,0.8f);

  gl_lightz light_01;
  light_01.set_light(lpos,lcol);

  /*
  texture setuptest_move to mesh
  */
  std::cout << "load texturez\n";

  texture_paramz_pak ship_tex_A3_parmz;
  ship_tex_A3_parmz.wm_s    = WarpMode::REPEAT;
  ship_tex_A3_parmz.wm_t    = WarpMode::REPEAT;
  ship_tex_A3_parmz.mag     = Filter::LINEAR;
  ship_tex_A3_parmz.min     = Filter::LINEAR;
  ship_tex_A3_parmz.path    = "data_extrn/ship_base_A03.bmp";
  ship_tex_A3_parmz.channels= 3;
  ship_tex_A3_parmz.unform_name = "active_texture_sampler";
  ship_tex_A3_parmz.tex_unit_index = 0;
  ship_tex_A3_parmz.text_type_flag = M_Tex_Flag::TEXTYR_BASIC;

  test_mesh.texture_setup(ship_tex_A3_parmz);
  test_mesh2.texture_setup(ship_tex_A3_parmz);

  /*
  lenz and other last min setupz or orgz.
  */

  std::cout << "load_lenz\n";

  view_lenz vl_01;

  glm::vec3 world_up(0.f,1.f,0.f);
  glm::vec3 lenz_front(0.f,0.f,-1.f);
  glm::vec3 lenz_pos(0.f,0.f,1.f);

  glm::mat4 view_matrix(1.f);
  view_matrix = glm::lookAt(lenz_pos,lenz_pos+lenz_front,world_up);

  float fov= 90.f;
  float near_plane = 0.1f;
  float far_plane = 1000.f;

  glm::mat4 Projection(1.f);
   Projection =  glm::perspective(glm::radians(fov),(float)MAIN_SCREEN_WIDTH /
                                     (float)MAIN_SCREEN_HIGHT,near_plane,far_plane);

  //shader_3.set_glm_mat4("projection",projection);
  float lenz_radius = 10.0f;
  //initbase controzfactoz

  /*
  * UNIFORM SETTUPzzz.
  */

  //itunformz!
  GLint frame_buf_width,frame_buf_hight;
  shader_3.use_shader();

  glm::mat4 view_projection = Projection*view_matrix;

  glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"view_projection"),
                                1,GL_FALSE,glm::value_ptr(view_projection));
                                /*
  glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"projection"),
                                1,GL_FALSE,glm::value_ptr(projection));

  glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"view"),
                                1,GL_FALSE,glm::value_ptr(view_matrix));*/

/*
* GOBAL OPEN GL ENABLEZ
*/

 glEnable(GL_DEPTH_TEST);
 glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

 /*
 Mainloopz!
 */

  std::cout <<"#####entering main loop setup compleate;\n \n";

  while(!glfwWindowShouldClose(glfw_window))
  {

    //process keyz
    process_input_glfw(glfw_window);


    /*
    BEGIN RENDER CYCLE! OHHH
    */
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // shaders to use globalyz
    shader_3.use_shader();

    //set projectionz
    glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

    Projection = glm::mat4(1.f);
    Projection = glm::perspective(glm::radians(fov),(float)frame_buf_width /
                                      (float)frame_buf_hight,near_plane,far_plane);
    view_projection =glm::mat4(1.f);
    view_projection = Projection*view_matrix;

    glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"view_projection"),
                                           1,GL_FALSE,glm::value_ptr(view_projection));
                                /*
    glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"projection"),
                                           1,GL_FALSE,glm::value_ptr(Projection));*/


    test_ajustship.rotation_ajust.y =0.09f;
    test_ajustship2.posz_ajust.x=-0.001f;
  //  test_ajustship2.rotation_ajust.y=-0.01f;
    //test_ajustship2.posz_ajust.x = -0.08f;
    test_mesh.update_mesh_model(test_ajustship);
    test_mesh2.update_mesh_model(test_ajustship2);

      //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
      //gl_run_render(glfw_window,shader_prt_vec,encaple_vaoz);
      test_mesh.draw(&shader_3);
      test_mesh2.draw(&shader_3);
      glfwSwapBuffers(glfw_window);

      //[postopz]
      //and poll glfw
      glfwPollEvents();

    }//endmain loop
/*
* CLEANUP GOES HERE
*/

  return 0;
      }
