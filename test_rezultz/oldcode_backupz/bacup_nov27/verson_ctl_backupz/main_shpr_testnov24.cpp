
#include "shader_parser.hpp"
#include "render_objk_cmd.hpp"
#include "geometry_parser.hpp"
#include "pre_comb_objz.hpp"
#include "geometry.hpp"



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


//float sin_green = sin(timeValue)/pow(cos(timeValue)*tan(timeValue)*tan(timeValue)*tan(timeValue),tan(timeValue)*tan(timeValue));
//float colour_angluretime = sin_green*pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
//float sin_tsnz = colour_angluretime*sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);
//std::cout << "sign_greenz:" <<sin_green<< "  anglure_colourval::" << colour_angluretime <<'\n';

for (size_t i =0; i<in_shaderz.size();i++)
{
  in_shaderz.at(i)->use_shader();
  int vertexColorLocation = glGetUniformLocation(in_shaderz.at(i)->program_ID, "ourColor");
  //std::cout << "vertex_colour_unform at::" << vertexColorLocation << "  Progamid::"
        //    << in_shaderz.at(i)->program_ID << "ourColor" << '\n';
  std::vector<GLuint> vao_vec  =  vetex_array_objkz.at(i);
  glUniform4f(vertexColorLocation, sin_tsnz, sin_green, colour_angluretime, 1.f);

//if(vao_has_model == true)
/*
  for(size_t i = 0; i<2;i++)
  {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,triangle_world_space[i]);
    float angle = 13.0f*(i+1)*colour_angluretime;
    model = glm::rotate(model,glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
    //shader_3.set_glm_mat4("model",model);
    glUniformMatrix4fv(vertex_cornate_model, 1, GL_FALSE,&model[0][0]);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
  }*/


//for the binding buffers do draw.
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
//glfwSetCursorPosCallback(glfw_window, mouse_callback);
//glfwSetScrollCallback(glfw_window, scroll_callback);

GLenum glewErr = glewInit();
std::cout << "glew_code::" << glewErr <<'\n' <<'\n';
glViewport( 0, 0, MAIN_SCREEN_WIDTH, MAIN_SCREEN_HIGHT );


/*
* SHADER SETUPZ
*/
gl_shader shader_1;
gl_shader shader_2;
gl_shader_t shader_3;
int errcode = run_parse();
shader_3.test_flags();
std::vector<shader_tuple_type*>*  shader_TV_ptr = return_ptr_shader_TV();


  //for(size_t i =0; i< shader_tuple_vec.size(); i++)
  shader_3.setup_shader_code(shader_TV_ptr->at(6));
  shader_3.setup_shader_code(shader_TV_ptr->at(5));
  std::vector<int> base_shader_idz;
  base_shader_idz.push_back(6);
  base_shader_idz.push_back(5);
  shader_3.create_link_program(base_shader_idz);
  shader_3.test_flags();

/*
working DATA for current test.
*/
//object creation or storage... ovlzy move out tooo compled obkjekz. butt good
//if need to visuals

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
              -0.05f,  0.5f, 0.6f,  1.0f, 0.4f, 0.7f, 1.0f,  // bottom right
               0.5f, -0.2f, -0.2f,  0.2f, 1.0f, 0.3f, 1.0f,  // bottom left
               0.2f,  0.5f, -0.5f,  0.1f, 1.0f, 1.0f, 1.0f, // top

               0.5f,  0.1f,  0.3f,  1.0f, 0.4f, 0.7f, 1.0f,  // bottom right
               0.5f, -0.2f, -0.6f,  0.2f, 1.0f, 0.3f, 1.0f,  // bottom left
              -0.2f,  0.9f, -0.7f,  0.1f, 1.0f, 1.0f, 1.0f, // top

               0.2f,  0.5f,  0.6f,  1.0f, 0.4f, 0.7f, 1.0f,  // bottom right
              -0.5f,  0.9f,  0.6f,  0.2f, 1.0f, 0.3f, 1.0f,  // bottom left
              -0.2f,  0.5f,  0.8f,  0.1f, 1.0f, 1.0f, 1.0f // top
          };



    /*
     *BUFFERZ MGMT CMDZ
    */
  //  ply_parser pp;
  //  pp.open_read_file("data_extrn/cube.ply");

    //std::cout << "file parsed objz" << '\n';

    //std::vector<float> verx_da_test2 = pp.return_vertex_xyz_data();
    //  std::cout << "vertexdata objz" << '\n';
    //std::vector<unsigned int> indices_da_test2 = pp.return_indices_data();
    //std::cout << "incadz objz" << '\n';
  //  size_t num_vex_test2 = pp.num_of_vertex_points() ;
  //  size_t count_indices_test2 = pp.num_of_indices() ;

    Wavefront_parser wp;
  //  wp.open_read_file("data_extrn/bbase.obj");

    //size_t test_size_indicatez =  wp.num_indicaez(0);
  //  std::cout << test_size_indicatez;
  //  wp.output_objdata();
    //objs_tuplez* test_tupleobj =  wp.return_tupled_ojk_at(0);
    std::vector<unsigned int> indicate_array;
    //indicate_array = wp.return_indices_data_at(0);
  //  std::vector<GLfloat> verx_da_test =  wp.return_vertex_data_at(0);
  //  size_t num_vertx_test1 = verx_da_test.size();

    wavefornt_parser2 wp2;
    //wp2.read_file("data_extrn/boat_Base.obj");
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
    wp2.return_data(vertices,uvs,normals);

//  std::vector<mesh_vertex> mesh_ver_1 = wp2.return_mesh_vec();
    //Texture_gl ship_base_texture_A1;
    //ship_base_texture_A1.load_bitmap_to_texture("data_extrn/ship_base_A02.bmp");

//meshsettup and gemomenty_lighting
std::string ship_res_textA2 = {"data_extrn/boat_Base_2.obj"};
mesh test_mesh;
test_mesh.init(&wp2,ship_res_textA2);
test_mesh.bindmesh_buf();

glm::vec3 lpos(1.2f,1.0f,2.0f);
glm::vec3 lcol(0.6f,0.2f,0.8f);

gl_lightz light_01;
light_01.set_light(lpos,lcol);






      unsigned int VAO4, Buff4;

      glGenVertexArrays(1, &VAO4);
      glGenBuffers(1,&Buff4);

      glBindVertexArray(VAO4);
      glBindBuffer(GL_ARRAY_BUFFER, Buff4);
      //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3)+uvs.size()*sizeof(glm::vec2), 0, GL_STATIC_DRAW);

      glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size() * sizeof(glm::vec3),&vertices[0]);
      glBufferSubData(GL_ARRAY_BUFFER,vertices.size() * sizeof(glm::vec3),uvs.size() *sizeof(glm::vec2),&uvs[0]);


      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(0);

     GLuint colorbuffer;
      glGenBuffers(1, &colorbuffer);
      glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(pre_comb_objz::rando_colour_data),pre_comb_objz::rando_colour_data, GL_STATIC_DRAW);

      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(1);

    //  GLuint texture_id_Ship_A1= ship_base_texture_A1.load_bitmap_to_GL();

      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  0, BUFFER_OFFSET(3 * sizeof(float)));

      Texture_gl ship_test_texture;
      ship_test_texture.set_texture_ST(WarpMode::REPEAT,'s');
      ship_test_texture.set_texture_ST(WarpMode::REPEAT,'t');
      ship_test_texture.set_min_Mag_Filter(Filter::LINEAR,'i');
      ship_test_texture.set_min_Mag_Filter(Filter::LINEAR,'a');
      ship_test_texture.load_texture("data_extrn/ship_base_A03.bmp",3);
      ship_test_texture.init_texture();

/*
      GLuint texture_ship_A1_ID;
      glGenTextures(1,&texture_ship_A1_ID);
      int width, height,n;
      unsigned char* image;
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,texture_ship_A1_ID);
      image = stbi_load(,&width,&height,&n,3); //SOIL_LOAD_RGB SOIL_LOAD_AUTO
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
      //glGenerateMipmap(GL_TEXTURE_2D);
      stbi_image_free(image);
*/

///
            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tri_01), vertices_tri_01, GL_STATIC_DRAW);
          // glBufferData(GL_ARRAY_BUFFER, size_data_01, verx_da_test.data(), GL_STATIC_DRAW);
            // position attribute
          //  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            /////
            /*
                  unsigned int IO3, Buff3;
                  //glGenVertexArrays(1, &VAO3);
                  //size_t size_data_01 = verx_da_test.size()* sizeof(GLfloat);

                  glGenBuffers(1, &Buff3);
                  glBindBuffer(GL_ARRAY_BUFFER, Buff3);
                  glBufferData(GL_ARRAY_BUFFER,num_vertx_test1* sizeof(GLfloat),verx_da_test.data(),GL_STATIC_DRAW);
                  glEnableVertexAttribArray(0);
                  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

                  glGenBuffers(1,&IO3);
                  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IO3);
                  glBufferData(GL_ELEMENT_ARRAY_BUFFER,test_size_indicatez* sizeof(unsigned int),indicate_array.data(),GL_STATIC_DRAW);
                  */


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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            ///

/*
DATASTURUCTRE MGMT CMDZ
*/
      //orginze the data and put it into datastructuresz.

      std::vector<GLuint> buffarry_obk_vec_01;
    //buffarry_obk_vec_01.push_back(VAO);
    //  buffarry_obk_vec_01.push_back(VAO1);
      //buffarry_obk_vec_01.push_back(VAO4);
      //buffarry_obk_vec_01.push_back(bvab_01.v_arry_O);
      std::vector<gl_shader_t*> shader_prt_vec;
      shader_prt_vec.push_back(&shader_3);


      std::vector<std::vector<GLuint>> encaple_vaoz;
      encaple_vaoz.push_back(buffarry_obk_vec_01);


      typedef std::tuple<unsigned int,std::vector<GLuint>,unsigned char> v_bArray_o_feture_tuple;
      using  vbArray_oft = v_bArray_o_feture_tuple;
      vbArray_oft m_vbArray_fetsp;


/*
lenz and other last min setupz or orgz.
*/

//setuing up projections and camra stuff
      view_lenz vl_01;

      //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)MAIN_SCREEN_WIDTH /
    //                                                               (float)MAIN_SCREEN_HIGHT, 0.1f, 100.0f);
      glm::vec3 world_up(0.f,1.f,0.f);
      glm::vec3 lenz_front(0.f,0.f,-1.f);
      glm::vec3 lenz_pos(0.f,0.f,1.f);

      glm::mat4 view_matrix(1.f);
      view_matrix = glm::lookAt(lenz_pos,lenz_pos+lenz_front,world_up);

      float fov= 90.f;
      float near_plane = 0.1f;
      float far_plane = 1000.f;

      glm::mat4 projection(1.f);
      glm::perspective(glm::radians(fov),(float)MAIN_SCREEN_WIDTH /
                                         (float)MAIN_SCREEN_HIGHT,near_plane,far_plane);

      //shader_3.set_glm_mat4("projection",projection);
      float lenz_radius = 10.0f;
      //initbase controzfactoz
      glm::vec3 posz_base(0.f);
      glm::vec3 rotation_base(0.f);
      glm::vec3 scale_base(0.2f);

      glm::mat4 base_model_matrix(1.0f);
      base_model_matrix = glm::translate(base_model_matrix, posz_base);
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
      base_model_matrix = glm::scale(base_model_matrix,scale_base);


      glm::vec3 triangle_world_space[] =
      {
       glm::vec3( 0.2f, 0.2f,  -0.1f),
       glm::vec3( -0.2f, 0.2f,  0.1f),
      };

//itunformz!
GLint frame_buf_width,frame_buf_hight;
shader_3.use_shader();
glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"model_matrix"),
                              1,GL_FALSE,glm::value_ptr(base_model_matrix));

glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"projection"),
                              1,GL_FALSE,glm::value_ptr(projection));

glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"view"),
                              1,GL_FALSE,glm::value_ptr(view_matrix));


    //texturez
ship_test_texture.set_texture_sampler_uniform(&shader_3);
ship_test_texture.set_Tex_paramz();
/*
  glUniform1i(glGetUniformLocation(shader_3.program_ID, "active_texture_sampler"), 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //GL_REPEAT//GL_CLAMP_TO_EDGE//GL_CLAMP_TO_BORDER//GL_MIRRORED_REPEAT
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
*/

  /*
  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
//GL_NEAREST_MIPMAP_NEAREST//GL_LINEAR_MIPMAP_NEAREST//GL_NEAREST_MIPMAP_LINEAR//GL_LINEAR_MIPMAP_LINEAR



      std::cout <<"#####entering main loop setup compleate;\n \n";

/*
Mainloopz!
*/
 glEnable(GL_DEPTH_TEST);
//glEnable(GL_CULL_FACE);
//glCullFace(GL_BACK);
//glFrontFace(GL_CW);

    while(!glfwWindowShouldClose(glfw_window))
    {

      //process keyz
      process_input_glfw(glfw_window);
/*
BEGIN RENDER CYCLE! OHHH
*/

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  glBindVertexArray(VAO);

      shader_3.use_shader();

      //set projectionz
      glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

      projection = glm::mat4(1.f);
      projection =glm::perspective(glm::radians(fov),(float)frame_buf_width /
                                        (float)frame_buf_hight,near_plane,far_plane);

      glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"projection"),
                                             1,GL_FALSE,glm::value_ptr(projection));

      //do movmentz and tranformz on models
      rotation_base.y +=0.08f;
      rotation_base.z -=0.01f;

      //loadchanges into model matrix
      base_model_matrix =glm::mat4(1.f);
      base_model_matrix = glm::translate(base_model_matrix, posz_base);
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
      base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
      base_model_matrix = glm::scale(base_model_matrix,scale_base);

      //set the model matrix
      glUniformMatrix4fv(glGetUniformLocation(shader_3.program_ID,"model_matrix"),
                                    1,GL_FALSE,glm::value_ptr(base_model_matrix));


        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
        gl_run_render(glfw_window,shader_prt_vec,encaple_vaoz);
        test_mesh.draw(&shader_3);
      //from fucionz

    //  glBindVertexArray(VAO4);

    //  glDrawArrays(GL_TRIANGLES, 0, vertices.size());



      /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_mesh2.return_elment_buf());
      glDrawElements(
      			GL_TRIANGLES,      // mode
      			test_mesh2.return_num_indices(),    // count
      			GL_UNSIGNED_INT,   // type
      			(void*)0           // element array buffer offset
      		);
          */
      //IO3, Buff3;

/*
       glBindBuffer(GL_ARRAY_BUFFER, Buff3);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IO3);
      // std::cout << "num of indicate" << indicate_array.size() <<'\n';
       glDrawElements(
      GL_TRIANGLES,      // mode
      test_size_indicatez,    // count
      GL_UNSIGNED_INT,   // type
      (void*)0           // element array buffer offset
      );
/*

       glDrawElements(
     GL_TRIANGLES,      // mode
     test_size_indicatez,    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );*/

// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// -------------------------------------------------------------------------------
    glfwSwapBuffers(glfw_window);


    //[postopz]
    //and poll glfw
    glfwPollEvents();


    }

  return 0;
}
