//levelbuilder.
#include "opengl_utilityz.hpp"
#include "scene.hpp"
#include "lenz.hpp"


bool read_file_to_buffer(GLuint &buffer, char* path)
{
  FILE* file;
  size_t filesize;

  file = fopen(path,"rb");
  fseek(file,0,SEEK_END);
  filesize = ftell(f);

  fseek(f,0,SEEK_SET);
  glBindBuffer(GL_COPY_WRITE_BUFFER,buffer);

  glBufferData(GL_COPY_WRITE_BUFFER,(GLsizei)filesize,NULL,GL_STATIC_DRAW);

  void * data = glMapBuffer(GL_COPY_WRITE_BUFFER,GL_WRITE_ONLY);

  fread(data,1,filesize,file);

  glUnmapBuffer(GL_COPY_WRITE_BUFFER);
  fclose(file);

}
void read_model_setup()
{

}

int write_models(model_ajustment in_ajust)
{
  ofstream write_file("scenez01.dat", ios::out | ios::binary);
     if(!write_file)
     {
        std::cout << "Cannot open file!" << '\n';
        return 1;
     }

     model_ajustment test_ajustship;
     model_ajustment test_ajustship2;

     test_ajustship.rotation_ajust = glm::vec3(0.f);
     test_ajustship.posz_ajust  = glm::vec3(0.f);
     test_ajustship.scale_ajust = glm::vec3(0.f);

     test_ajustship2.rotation_ajust = glm::vec3(0.f);
     test_ajustship2.posz_ajust  = glm::vec3(0.f);
     test_ajustship2.scale_ajust = glm::vec3(0.f);

     model_ajustment ship_2_orgin;

     ship_2_orgin.posz_ajust.x=0.9f;
     ship_2_orgin.posz_ajust.y=0.5f;
     ship_2_orgin.posz_ajust.z= -0.1f;
     ship_2_orgin.scale_ajust = glm::vec3(0.1f);
     ship_2_orgin.rotation_ajust.y = 120.f;
     ship_2_orgin.rotation_ajust.x = 0.f;
     ship_2_orgin.rotation_ajust.z = 0.f;

     Meterialz meteral;

     std::array<model_ajustment,3> model_array;

     model_array[0] =ship_2_orgin;
     model_array[1] =test_ajustship2;
     model_array[2] =test_ajustship;
     for(size_t i =0; i<model_array.size(); i++)
     {
       write_file.write((char *) &model_array[i], sizeof(model_ajustment));
     }

   }
