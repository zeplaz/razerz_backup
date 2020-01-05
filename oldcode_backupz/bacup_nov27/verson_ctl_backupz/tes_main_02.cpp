
#include "mathII.hpp"
#include "mathz.hpp"
#include "colour.hpp"
#include "gl_lib_z.hpp"
#include "render_objk.hpp"

#include <tuple>
#include <forward_list>

#include "skybox_exmp/shader.hpp"

//`sdl2-config --cflags --libs`
#include <SDL.h>
#include <SDL_image.h>


//#include <SDL_opengles2.h>

/*
  g++ -std=c++17  -Wall -Wextra -pedantic tes_main_02.cpp
 `sdl2-config --cflags --libs` -lSDL2_image -lGL -lglut -lGLEW
*/
//typedefzforeasz
#define GET_FET_FLAGZ 0
#define GET_FET_POS_SIZE 1
#define GET_FET_COLOUR_SIZE 2
#define GET_FET_NUMVERX 3
#define GET_FET_POS_DATA 4
#define GET_FET_COLOUR_DATA 5

typedef std::tuple<unsigned char,int,int,int,GLfloat*,GLfloat*> f_sp_tuple;
typedef std::forward_list<gl_shader*> gobal_shader_list;

//gobvals
static gobal_shader_list gl_g_shad_list;

auto get_buf_oset = [](f_sp_tuple& fetu_tup)
{
  return std::get<GET_FET_NUMVERX>(fetu_tup);
};

void shutdown_key(int code)
{
   SDL_Quit( );
   exit( code );
}

static void handle_keyboard_DOWN(SDL_Keysym* keysignal)
{
  switch(keysignal->sym)
  {
    case SDLK_ESCAPE : shutdown_key(0);
    break;

    default :
    break;
  }
}

// The positons of the position and color data within the VAO


/*handling buffers
*******************
* vertex_vec3,vec3[]
* colourz_vec4 vec4[]
* glBufferSubData(GL_ARRAY_BUFFER,0,)
*/
/*
#define GET_FET_FLAGZ 0
#define GET_FET_POS_SIZE 1
#define GET_FET_COLOUR_SIZE 2
#define GET_FET_NUMVERX 3
#define GET_FET_POS_DATA 4
#define GET_FET_COLOUR_DATA 5
*/

void load_gl_buffer(GLuint& buffer, f_sp_tuple& in_feturez)
{
  bool continz = true;
  glGenBuffers(1,&buffer);
  glBindBuffer(GL_ARRAY_BUFFER,buffer);

//  std::get<GET_FET_POS_SIZE>(in_feturez)
  //std::get<GET_FET_COLOUR_SIZE>(in_feturez)
//  std::get<GET_FET_NUMVERX>(in_feturez)
//

  /*
  size_t pos_space = num_prtz*pos_depth*sizeof(GLfloat);
  size_t colour_space = num_prtz*colour_depth*sizeof(GLfloat);
  size_t feture_toal_space = pos_space+colour_space;
*/

size_t pos_space = std::get<GET_FET_NUMVERX>(in_feturez)*std::get<GET_FET_POS_SIZE>(in_feturez)*sizeof(GLfloat);
size_t colour_space = std::get<GET_FET_NUMVERX>(in_feturez)*std::get<GET_FET_COLOUR_SIZE>(in_feturez)*sizeof(GLfloat);
size_t feture_toal_space = pos_space+colour_space;

  switch(std::get<GET_FET_FLAGZ>(in_feturez))
  {
    case ATTRBUT_STATIC :
    glBufferData(GL_ARRAY_BUFFER,feture_toal_space, NULL, GL_STATIC_DRAW);

    break;

    case ATTRBUT_DYNAMIC_DRAW :
    glBufferData(GL_ARRAY_BUFFER, feture_toal_space, NULL, GL_DYNAMIC_DRAW);

    break;

    case ATTRBUT_STREAM :
    glBufferData(GL_ARRAY_BUFFER,feture_toal_space, NULL, GL_STREAM_DRAW);

    break;
    default :
    std::cout <<"no flag set for buffertype...orwhav no buf data set?\n";
    continz = false;
    break;
  }

  if(!continz)
  {
    glBufferSubData(GL_ARRAY_BUFFER,0,pos_space,std::get<GET_FET_POS_DATA>(in_feturez));
    glBufferSubData(GL_ARRAY_BUFFER,pos_space,colour_space,std::get<GET_FET_COLOUR_DATA>(in_feturez));
  }

}
//aftershaders insalled
//fulltransunifrmlocaion = glGetUniformLocation(ProgramID,"final_proj_matrix");

/*settup_Vertex_array_Objeck*/
GLuint indexable_VAO(int size, GLuint* indeicz)
{
  GLuint index_Vr_buf_ob;
  glGenBuffers(1,&index_Vr_buf_ob);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_Vr_buf_ob);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,size*sizeof(GLuint),indeicz,GL_DYNAMIC_DRAW);

  return index_Vr_buf_ob;
}


void settup_Vertex_array_Objeck(GLuint shader_pos,GLuint shader_colour,GLuint programID, int num_arrayz, GLuint* vao_array,f_sp_tuple& in_fetu_tuple, GLuint* buffer_in_array)
{

  glGenVertexArrays(num_arrayz,vao_array);

  for(size_t i = 0; i< sizeof(vao_array);i++)
  {
    glBindVertexArray(vao_array[i]);
    load_gl_buffer(buffer_in_array[i],in_fetu_tuple);
    glEnableVertexAttribArray(shader_pos);
    glEnableVertexAttribArray(shader_colour);
    glBindBuffer(GL_ARRAY_BUFFER,buffer_in_array[i]);
    glVertexAttribPointer(shader_pos,3,GL_FLOAT,GL_FALSE,0,0);
    glVertexAttribPointer(shader_colour,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(get_buf_oset(in_fetu_tuple)*3*sizeof(GLfloat)));

  }
}

  //drawtypes
  //gl(glBufferData(GL_ARRAY_BUFFER,sizeof(float_array_data),float_array_data,GL_X_Y)
  //STREAM | STATIC | DYNAMIC
  //DRAW|READ|COPY
  void render_elementz_indcatez(int num_indcz,render_mode r_mode)
  {

    if(r_mode ==render_mode::WIREFRAME)
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    glDrawElements(GL_TRIANGLES,num_indcz,GL_UNSIGNED_INT,NULL);
  }

  void render_vertex_array(int num_vertx)
  {
    glDrawArrays(GL_TRIANGLE_FAN, 0,num_vertx);
  }

  static void draw_gl(SDL_Window* window)
  {


    //glEnableVertexAttribArray(colorAttributeIndex);
    glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glDrawElements(GL_TRIANGLES,num_indcz,GL_UNSIGNED_INT,NULL);
    //
    //glutSwapBuffers();
    //in render
    /*
  for(size_t i = 0; i< VAO_Main_array_ID.size();i++)
  {
      glBindVertexArray(VAO_Main_array_ID[i])
      glm::mat4 model_toW = glm::tranz *roate
      fulltranzmatz_porj = model_tooW * world_proj_matix;
      glUniformMatrix4fv(fulltranUnifm_loc,1,GL_FALSE,&fulltranzmatz_porj[0][0]);
      glDrawElements(GL_TRIANGLES,indicatz[i],GL_UNSIGNED_SHORT,0);
  }
  */
}


void change_viewport(int w ,int h)
{
  glViewport(0,0,w,h);
}

void glut_render()
{
  glClearColor( 0, 0, 0, 0 );
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  for ( auto it_shader = gl_g_shad_list.begin(); it_shader != gl_g_shad_list.end(); ++it_shader )
    {
      gl_shader* shader_prt = *it_shader;
      shader_prt->use_shader();
      render_elementz_indcatez(12,render_mode::FILL);
      render_vertex_array(144);
    }




  //glBindBuffer()

  glutSwapBuffers();
}

int main(int argc, char* argv[])
{

  const int COLOUR_H = 4;
  const int POS_H = 3;
  const int OPJ_BUF_FLAGZ_DEFULT = ATTRBUT_DYNAMIC_DRAW;

  float dt = 0.0f;
  int lastFrame = 0;

  int colour_depth_widow = 0;
  bool quit = false;


  glutInitContextProfile(GLUT_CORE_PROFILE );

  //SDL_Event Prim_SDL_event;
  //SDL_Window *prt_window_main = nullptr;

  //const SDL_VideoInfo* info = NULL;
/*
  SDL_Init(SDL_INIT_EVERYTHING);
  //info = SDL_GetVideoInfo();
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
*/
  Uint32 w_flags = SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;

//setup some base_casesz
  GLuint VAO_array_IDz[2];
  int feture_spaceAttrbuz[7];
  GLfloat colour_pixel_cube[144];
  f_sp_tuple feture_space_tuple;
  GLuint gl_bufferz[5];
  //336 S..


    /*glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("cmGLUTZ_toolz");
    glutReshapeFunc(change_viewport);
    glutDisplayFunc(glut_render);

    */


//SDL_Surface *screen;


/*prt_window_main = SDL_CreateWindow( "cmdz_Toolz:", SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED, MAIN_SCREEN_WIDTH,
                                      MAIN_SCREEN_HIGHT,w_flags);
if( prt_window_main == nullptr )
 {
  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
 }
 */
    //load other openGLFeturez
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

  //  SDL_GLContext ctx = SDL_GL_CreateContext(prt_window_main);
  //  SDL_GL_MakeCurrent(prt_window_main,ctx);
  //  SDL_GL_SetSwapInterval(1);




//setup shaderz...

  GLuint gl_prgm_01_ID;

  gl_shader shader_01;
  gl_g_shad_list.push_front(&shader_01);

  shader_01.create_shader(shader_type::VERTEX_SHADER);
  //shader_01.create_shader(shader_type::FRAGMENT_SHADER);

  shader_01.get_shader_code("vertex_shader_01.glsl" ,shader_type::VERTEX_SHADER);
  //shader_01.get_shader_code(c ,path,shader_type::FRAGMENT_SHADER);
  gl_prgm_01_ID = glCreateProgram();

  glAttachShader(gl_prgm_01_ID,shader_01.vertex_shader_ID);

  glLinkProgram(gl_prgm_01_ID);

    shader_01.set_attrabutes(gl_prgm_01_ID);

    glValidateProgram(gl_prgm_01_ID);
    /*
  glGetProgramiv(gl_prgm_01_ID, GL_VALIDATE_STATUS, &Success);
  if (!Success)
  {
    glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
    std::cerr << "Invalid shader program: " << ErrorLog << std::endl;
    return false;
  }*/

    //glShaderSource(frag_shader_01_ID,1,(const GLchar**)&frag_shader_source,NULL);
    //glCompileShader(frag_shader_01_ID);

    //glGetShaderInfoLog(vertex_shader_01_ID,MAX_LOG,logsize,log2_shader);
    //std::cout << log2_shader<< '\n';
    //glAttachShader(gl_prgm_01_ID,frag_shader_01_ID);

    //glGetProgramiv(gl_prgm_01_ID, GL_LINK_STATUS, &linked);

    //glGetProgramInfoLog(gl_prgm_01_ID,MAX_LOG,logsize,log_shader);

    //std::cout << log_shader<< '\n';
    //use via

  //  Shader shader_glsl_VS_01("vertex_shader_01.glsl")
    //Shader skyboxShader("skybox_exmp/6.2.skybox.vs", "skybox_exmp/6.2.skybox.fs");
  //  Shader shader("skybox_exmp/6.1.cubemaps.vs", "skybox_exmp/6.1.cubemaps.fs");
    std::cout << "shaderloader \n";
   bool pass;
  //  = buffer_setup_ojkz();
   if(pass==false)
   {
     quit =true;
   }

   PolyF3D test_poly;
   std::cout << "skyboxvec_name_size::" << pre_comb_objz::sky_box_sample.size() <<'\n';


   view_lenz prim_view_lens;

   std::cout << "comleated primaryload. creativo AVOZ\n";


//VOAZZZZ

GLuint tri_Index_Obk_01_ID;
tri_Index_Obk_01_ID= indexable_VAO(12,pre_comb_objz::index_buf_triagle);



settup_Vertex_array_Objeck(shader_01.shader_pos,shader_01.shader_colour,gl_prgm_01_ID,2,VAO_array_IDz,feture_space_tuple,gl_bufferz);

   // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pre_comb_objz::skyboxVertices), &pre_comb_objz::skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(skyboxVAO);
    glEnableVertexAttribArray(shader_01.shader_pos);
    glEnableVertexAttribArray(shader_01.shader_colour);
    glVertexAttribPointer(shader_01.shader_pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glVertexAttribPointer(shader_colour,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(get_buf_oset(in_fetu_tuple)*3*sizeof(GLfloat)));




    std::cout << "AVOZ done\n";
    //skyboxShader.use();
  //  skyboxShader.setInt("skybox", 0);

  //  shader.use();
  //  shader.setInt("texture1", 0);

    std::cout << "done\n";
    int currentFrame;
    int delta_int;
    quit = false;

    glClearColor( 0, 0, 0, 0 );




    cube_gl cube_01;
    cube_01.set_cube(pre_comb_objz::g_Indices_cube01,pre_comb_objz::cubeVertices_01,ATTRBUT_DYNAMIC_DRAW);

  //  int linkage_secure = glGetProgramiv(GL_LINK_STATUS, &linked);


  glutMainLoop();

  /*
  while(!quit)

  {
    //std::cout << "loopPRIMARYoutside\n";
    //screen = SDL_GetWindowSurface(prt_window_main);

    while( SDL_PollEvent( &Prim_SDL_event ) != 0 )
    {
      if( Prim_SDL_event.type == SDL_QUIT )
      {
        quit = true;
      }

        currentFrame = glutGet(GLUT_ELAPSED_TIME);
        dt = (currentFrame - lastFrame)/1000;
        lastFrame = currentFrame;

       //
       //
  //  SDL_UpdateWindowSurface(prt_window_main);
  if (Prim_SDL_event.type == SDL_KEYDOWN)
  {
    switch(Prim_SDL_event.key.keysym.sym)
    {
    case SDLK_w :

      prim_view_lens.Process_keyboard(Camera_Movement::FORWARD,dt);
      break;
    case SDLK_s :
      prim_view_lens.Process_keyboard(Camera_Movement::BACKWARD,dt);
      break;
    case SDLK_d :
      prim_view_lens.Process_keyboard(Camera_Movement::LEFT,dt);
      break;
    case SDLK_a :
      prim_view_lens.Process_keyboard(Camera_Movement::RIGHT,dt);
      break;
   default :
   break;
      }
  }


  //  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // render_elementz_indcatez(12,render_mode::FILL);
   //render_vertex_array(144);

   //SDL_GL_SwapWindow(prt_window_main);

      //  shader.use();
    //    glm::mat4 model = glm::mat4(1.0f);
    //    glm::mat4 view = prim_view_lens.Get_view_eulrz();
    //    glm::mat4 projection = prim_view_lens.lenz_projection();
  //      shader.setMat4("model", model);
  //      shader.setMat4("view", view);
//        shader.setMat4("projection", projection);

//   glDepthFunc(GL_LEQUAL);
//   skyboxShader.use();

  // skyboxShader.setMat4("view",prim_view_lens.Get_view_eulrz());
//   skyboxShader.setMat4("projection",prim_view_lens.lenz_projection());

   //skybox
  // glBindVertexArray(skyboxVAO);
//   glActiveTexture(GL_TEXTURE0);

  // glBindTexture(GL_TEXTURE_CUBE_MAP, sky_box_id);
//   glDrawArrays(GL_TRIANGLES, 0, 36);
  //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//   glBindVertexArray(0);
//   glDepthFunc(GL_LESS);
   //SDL_GL_SwapWindow(prt_window_main);
   //draw_gl();
  }
}*/


  //SDL_GL_DeleteContext(ctx);
  //SDL_DestroyWindow(prt_window_main);
  //glfwTerminate();
  //SDL_Quit();

return 0;
}




/*
Use SDL_GetWindowSize() to query the
client area's size in screen coordinates,
and SDL_GL_GetDrawableSize() or SDL_GetRendererOutputSize()
to query the drawable size in pixels.
*/
