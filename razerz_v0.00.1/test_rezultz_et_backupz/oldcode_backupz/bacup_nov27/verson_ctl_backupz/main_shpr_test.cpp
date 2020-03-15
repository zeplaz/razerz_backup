
#include "shader_parser.hpp"
#include "render_objk_cmd.hpp"



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
  std::cout <<"\n ###nummof shaders to process" << in_shaderz.size() << "  num of objket packagez::" << vetex_array_objkz.size() << '\n' << '\n';
float timeValue = glfwGetTime();
float sin_green = sin(timeValue);
float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);

//std::cout << "sign_greenz:" <<sin_green<< "  anglure_colourval::" << colour_angluretime <<'\n';

for (size_t i =0; i<in_shaderz.size();i++)
{
  in_shaderz.at(i)->use_shader();
  int vertexColorLocation = glGetUniformLocation(in_shaderz.at(i)->program_ID, "ourColor");
  //std::cout << "vertex_colour_unform at::" << vertexColorLocation << "  Progamid::"
        //    << in_shaderz.at(i)->program_ID << "ourColor" << '\n';
  std::vector<GLuint> vao_vec  =  vetex_array_objkz.at(i);
  glUniform4f(vertexColorLocation, sin_tsnz, sin_green, colour_angluretime, 0.5f);

  for(size_t k=0; k<vao_vec.size();k++)
  {
   std::cout << "binding:voa:" << vao_vec.at(k) << '\n';

   glBindVertexArray(vao_vec.at(k));
   glDrawArrays(GL_TRIANGLES, 0, 3);
  }

}

}

int main(int argc, char* argv[])
{
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
//glfwSetCursorPosCallback(window, mouse_callback);
//glfwSetScrollCallback(window, scroll_callback);

GLenum glewErr = glewInit();
std::cout << "glew_code::" << glewErr <<'\n' <<'\n';
glViewport( 0, 0, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HIGHT );

gl_shader shader_1;
gl_shader shader_2;
gl_shader_t shader_3;
int errcode = run_parse();
shader_3.test_flags();
std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();


  //for(size_t i =0; i< shader_tuple_vec.size(); i++)
  shader_3.setup_shader_code(shader_TV_ptr->at(4));
  shader_3.setup_shader_code(shader_TV_ptr->at(5));
  std::vector<int> base_shader_idz;
  base_shader_idz.push_back(4);
  base_shader_idz.push_back(5);
  shader_3.create_link_program(base_shader_idz);
  shader_3.test_flags();


  tri_base_poly3d trian_02;
  Basic_vertex_array_buffer bvab_01;

  trian_02.set_vertexz(0.1f,-0.2f,0.3f,
                       0.7f,-0.4f,0.7f,
                       -0.4f,0.2f,-0.7f);

  trian_02.set_colour_base(0.40f,0.30f,0.7f,1.0f,
                           0.24f,0.13f,0.7f,1.0f,
                           0.14f,0.3f,0.17f,1.0f
                          );

  GLfloat* ptr_verx_tri;
  GLfloat* ptr_colour_tri;
   ptr_verx_tri   = trian_02.tri_vertex;
   ptr_colour_tri = trian_02.colourRGBA;
  bvab_01.set_verx_via_pos_col(ptr_verx_tri,ptr_colour_tri);

  float vertices_tri_01[] = {
          // positions         // colors
           0.5f, -0.5f, 0.6f,  1.0f, 0.4f, 0.3f,  // bottom right
          -0.5f, -0.2f, 0.6f,  -0.3f, 1.0f, 0.0f,  // bottom left
           0.4f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f   // top

      };

    float vertices_tri_02[] = {
              // positions         // colors
               -0.5f, 0.5f, 0.6f,  1.0f, 0.4f, 0.7f,  1.0f,  // bottom right
               0.5f, -0.2f, -0.6f,  0.2f, 1.0f, 0.3f, 1.0f,  // bottom left
               0.2f,  0.5f, -0.5f,  0.1f, 1.0f, 1.0f,  1.0f // top
          };

      unsigned int VBO, VAO;
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArray(VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tri_01), vertices_tri_01, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      // color attribute
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
      glEnableVertexAttribArray(1);


////
      unsigned int VBO1, VAO1;
      glGenVertexArrays(1, &VAO1);
      glGenBuffers(1, &VBO1);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArray(VAO1);

      glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    //  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float),&trian_02.tri_vertex);
    //  glBufferSubData(GL_ARRAY_BUFFER,9*sizeof(float),4*sizeof(float),&trian_02.colourRGBA);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tri_02), vertices_tri_02, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      // color attribute
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
      glEnableVertexAttribArray(1);

      std::vector<GLuint> buffarry_obk_vec_01;
      buffarry_obk_vec_01.push_back(VAO);
      buffarry_obk_vec_01.push_back(VAO1);
      //buffarry_obk_vec_01.push_back(bvab_01.v_arry_O);
      std::vector<gl_shader_t*> shader_prt_vec;
      shader_prt_vec.push_back(&shader_3);
      std::vector<std::vector<GLuint>> encaple_vaoz;
      encaple_vaoz.push_back(buffarry_obk_vec_01);

//setuing up projections and camra stuff
      view_lenz vl_01;

      glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)MAIN_SCREEN_WIDTH / (float)MAIN_SCREEN_HIGHT, 0.1f, 100.0f);
      shader_3.set_glm_mat4("projection",projection);
      float lenz_radius = 10.0f;


      glm::vec3 triangle_world_space[] =
      {
       glm::vec3( 0.2f, 0.2f,  -0.1f),
       glm::vec3( -0.2f, 0.2f,  0.1f),
      };

      std::cout <<"#####entering main loop setup compleate;\n \n";

    while(!glfwWindowShouldClose(glfw_window))
    {
      process_input_glfw(glfw_window);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


      glBindVertexArray(VAO);
    //  glDrawArrays(GL_TRIANGLES, 0, 3);
/*
    float timeValue = glfwGetTime();
    float sin_green = sin(timeValue);
    float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
    float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);
*/
      shader_3.use_shader();
/*
      int vertexColorLocation = glGetUniformLocation(shader_3.program_ID, "ourColor");
      glUniform4f(vertexColorLocation, sin_tsnz, sin_green, colour_angluretime, 0.5f);

      glm::mat4 view = glm::mat4(1.0f);
      float lenz_x = sin(timeValue)*lenz_radius;
      float lenz_z = cos(timeValue)*lenz_radius;
      view = glm::lookAt(glm::vec3(lenz_x, 0.0f, lenz_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

      int vertex_cornate_model = glGetUniformLocation(shader_3.program_ID,"model");

    //shader_3.set_glm_mat4("view",view);

      glBindVertexArray(VAO);
      for(size_t i = 0; i<2;i++)
      {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,triangle_world_space[i]);
        float angle = 13.0f*(i+1)*colour_angluretime;
        model = glm::rotate(model,glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
        //shader_3.set_glm_mat4("model",model);
        glUniformMatrix4fv(vertex_cornate_model, 1, GL_FALSE,&model[0][0]);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
      }
*/
      gl_run_render(glfw_window,shader_prt_vec,encaple_vaoz);
      //from fucionz


// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// -------------------------------------------------------------------------------
    glfwSwapBuffers(glfw_window);
    glfwPollEvents();

    }

  return 0;
}
