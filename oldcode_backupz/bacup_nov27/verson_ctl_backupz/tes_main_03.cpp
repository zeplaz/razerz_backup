//main_refactoe3

/*
complie stuff
g++ -std=c++17  -Wall -Wextra -pedantic tes_main_03.cpp gl_lib_z.cpp render_objk.cpp
`pkg-config --cflags gldw3 --libs glfw3` -lSDL2_image -lGL -lglut
-lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11


*/

#include "mathII.hpp"
#include "mathz.hpp"
#include "colour.hpp"
#include "gl_lib_z.hpp"
#include "render_objk.hpp"
#include "pre_comb_objz.hpp"

#include <forward_list>

#include "skybox_exmp/shader.hpp"

  GLvoid GLAPIENTRY opengl_callback_func(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam)

            {
              std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: "<< message << std::endl;
    std::cout << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity){
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}



//gobvals
typedef std::forward_list<gl_shader*> gobal_shader_list;

static gobal_shader_list gl_g_shad_list;

int main(int argc, char* argv[])
{

  const int COLOUR_H = 4;
  const int POS_H = 3;
  const int OPJ_BUF_FLAGZ_DEFULT = ATTRBUT_DYNAMIC_DRAW;

  float dt = 0.0f;
  int lastFrame = 0;

  int colour_depth_widow = 0;
  bool quit = false;

//setup some base_casesz
  GLfloat colour_pixel_cube[144];
  GLuint gl_bufferz[5];

  int currentFrame;
  int delta_int;

  GLFWwindow * glfw_window;

  std::string fragment_shader
  =
  "#version 330 core\n"
  "\n"
  "layout(location=0) out vec4 color;\n"
  "\n"
  "void main()\n"
  "{\n"
  "   color = vec4(1.0,0.0,0.0,1.0);\n"
  "}\n";

  for(int i = 0; i<6;i++)
  { for(int k =0; k<24;k++)
    {
    colour_pixel_cube[(k*i)+k] = pre_comb_objz::base_colour_sampz[k];
    }
  }

  f_sp_tuple feture_space_tuple = std::make_tuple(OPJ_BUF_FLAGZ_DEFULT,COLOUR_H,POS_H,144,
                                       pre_comb_objz::samplecube_02,colour_pixel_cube);


  glewExperimental = GL_TRUE;
  //launch gluitInit

  if (!glfwInit())
{
    // Initialization failed
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

  GLenum glewErr = glewInit();
  std::cout << "glew_code::" << glewErr;

  if(glDebugMessageCallback)
  {
    std::cout << "Register OpenGL debug callback " << std::endl;
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_callback_func, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE,
      GL_DONT_CARE,
      GL_DONT_CARE,
      0,
      &unusedIds,
      true);
  }
   else
    {std::cout << "glDebugMessageCallback not available" << std::endl;}


  //settings for opengl
  /* Our shading model--Gouraud (smooth). */
  glShadeModel(GL_SMOOTH);
  /* Culling. */
  //glCullFace( GL_BACK );
  //glFrontFace( GL_CCW );
  //glEnable( GL_CULL_FACE );
  glViewport( 0, 0, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HIGHT );
  //glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
  //glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
  //glOrtho( 0, MAIN_SCREEN_WIDTH, 0, MAIN_SCREEN_WIDTH, 0, 1 ); // essentially set coordinate system
  //glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
  //  glLoadIdentity(); // same as above comment
  glPolygonMode( GL_FRONT_AND_BACK,GL_FILL);

//setup shaderz...

  GLuint gl_prgm_01_ID;

  gl_shader shader_01;
  gl_g_shad_list.push_front(&shader_01);

  shader_01.create_shader(shader_type::VERTEX_SHADER);
  //shader_01.create_shader(shader_type::FRAGMENT_SHADER);

  shader_01.get_shader_code("vertex_shader_01.glsl", shader_type::VERTEX_SHADER);
  shader_01.load_shader_complie();
  shader_01.get_shader_code(fragment_shader,shader_type::FRAGMENT_SHADER);
  shader_01.load_shader_complie();

  gl_prgm_01_ID = glCreateProgram();

  glAttachShader(gl_prgm_01_ID,shader_01.vertex_shader_ID);
  glAttachShader(gl_prgm_01_ID,shader_01.frag_shader_ID);
  glLinkProgram(gl_prgm_01_ID);

  shader_01.set_attrabutes(gl_prgm_01_ID);

  glValidateProgram(gl_prgm_01_ID);

  std::cout << "shaderloaderd \n";

  //inliaze some objects and lens
  view_lenz prim_view_lens;





  unsigned int sky_box_id = load_skybox_GL(pre_comb_objz::sky_box_sample);

  std::cout << "comleated primaryload. creativo AVOZ\n";

  //create Budderz
  Basic_vertex_array_buffer BVA_buf_01;

  BVA_buf_01.set_Verx_buf(pre_comb_objz::samplecube_02,sizeof(GLfloat)*6*4*3);


  //pre_comb_objz::triangle_vertixz_01,sizeof(GLfloat)*5*3
  ///VOAZZZ

  //draw_able_gl gl_objk_01;
//  draw_able_gl gl_objk_02;
//  GLuint VAO_array_IDz[2];
/*
  gl_objk_01.settup_Vertex_array_Objeck(shader_01.shader_pos,shader_01.shader_colour,
                            gl_prgm_01_ID,2,VAO_array_IDz,feture_space_tuple,gl_bufferz);

  std::cout << "###AVOZ01\n";
  gl_objk_02.setup_obj_indeictable(12,pre_comb_objz::index_buf_triagle);

  std::cout << "###AVOZ02\n";
  gl_objk_02.indexable_VAO();
  std::cout << "###cube\n";
*/
  cube_gl cube_01;

  cube_01.set_cube(pre_comb_objz::g_Indices_cube01,pre_comb_objz::cubeVertices_01,ATTRBUT_DYNAMIC_DRAW);

  //#define ASSERT(x)

    //std::cout << "ERROR::(" << glGetError() << ')' << '\n';


 std::cout << "entering loop;\n";
  while(!glfwWindowShouldClose(glfw_window))
  {
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    shader_01.use_shader();


    //gl_objk_02.render_elementz_indcatez();
    //gl_objk_02.clear_bufferz(shader_01);
  //  gl_objk_01.render_elementz_indcatez();

    //glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,nullptr);


    glfwSwapBuffers(glfw_window);

    glfwPollEvents();
  }
  glfwTerminate();

return 0;
}
