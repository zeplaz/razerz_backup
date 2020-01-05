#pragma once


#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <regex>
#include <utility>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <array>

#include "gl_lib_z.hpp"
#include "geometry.hpp"

typedef struct vertex_data_type
{
  float x;
  float y;
  float z;
}vertex_data;

typedef struct indices_raw_type
{
  unsigned int indicez3[3];
  int operator[](int i) { return indicez3[i];}

}indices_raw;

typedef struct face_type
{
  std::vector<indices_raw> indicesz_data;

}face;


typedef std::tuple<int,std::pair<std::string,int>,std::vector<vertex_data>,std::vector<face>> objs_tuplez;
typedef std::tuple<std::array<float,3>,std::array<float,3>,std::array<float,2>> element_vertex_tuple;

typedef struct vertex_type
{
  glm::vec3 v_position;
  glm::vec3 v_normal;
  glm::vec2 v_textcord;

  bool operator<(const vertex_type that) const{
		return memcmp((void*)this, (void*)&that, sizeof(vertex_type))>0;}
} mesh_vertex;

typedef struct parsed_paket_type
{
  parsed_paket_type(std::vector<glm::vec3> in_vertices,
              std::vector<glm::vec3> in_normals,
              std::vector<glm::vec2> in_uvs)
  {
    std::vector<glm::vec3> vertices =in_vertices;
    std::vector<glm::vec3> normals  =in_normals;
    std::vector<glm::vec2> uvs      =in_uvs;
  }

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;

}parsed_paket;


class wavefornt_parser2
{
  private :

  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

  public :
  void cleanup_paket(parsed_paket* in_pak)
  {
    in_pak->vertices.clear();
    in_pak->uvs.clear();
    in_pak->normals.clear();
    delete in_pak;
  }
  parsed_paket* gen_parse_parket(std::vector < glm::vec3 > & in_vertices,
                                  std::vector < glm::vec3 > & in_normals,
                                  std::vector < glm::vec2 > & in_uvs)
    {
      parsed_paket* temp_pak = new parsed_paket(in_vertices,in_normals,in_uvs);
      return temp_pak;
    }



  std::pair<std::vector<mesh_vertex>*,std::vector<unsigned int>*> read_file(std::string path)
  {
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    std::vector<mesh_vertex>* mesh_v_prt = new  std::vector<mesh_vertex>();

    FILE* file = fopen(path.c_str(),"r");
    if(file == NULL)
    {
      printf("failto openfile \n");
      fclose(file);
      return std::make_pair(nullptr,nullptr);
    }
    else
    {

    while(1)
    {
      char line_header[255];
      int res = fscanf(file,"%s",line_header);
      if(res == EOF)
      break;
      if(strcmp(line_header, "v") ==0)
      {
        glm::vec3 vertex;
        fscanf(file,"%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
      }
      else if( strcmp( line_header, "vt" ) == 0 )
      {
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        temp_uvs.push_back(uv);
      }
      else if ( strcmp( line_header, "vn" ) == 0 )
      {
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
      }
      else if ( strcmp( line_header, "f" ) == 0 )
      {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9)
        {
            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            return  std::make_pair(nullptr,nullptr);
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
    }
  }
  fclose(file);

  for(unsigned int i=0; i< vertexIndices.size();i++)
  {
    mesh_vertex t_mv;
    unsigned int vertexIndex_current = vertexIndices[i];
    unsigned int IndicesIndex_current = uvIndices[i];
    unsigned int normalIndex_current = normalIndices[i];
    glm::vec3 vertex = temp_vertices[ vertexIndex_current-1 ];
    glm::vec3 normz = temp_normals[normalIndex_current-1];
    glm::vec2 uvz = temp_uvs[IndicesIndex_current-1];
    t_mv.v_position =vertex;
    t_mv.v_normal   =normz;
    t_mv.v_textcord = uvz;
    mesh_v_prt->push_back(t_mv);
  }
/*
  for( unsigned int i=0; i<vertexIndices.size(); i++ )
  {
    unsigned int vertexIndex_current = vertexIndices[i];
    glm::vec3 vertex = temp_vertices[ vertexIndex_current-1 ];
    vertices.push_back(vertex);
  }
  for( unsigned int i=0; i<uvIndices.size(); i++ )
  {
    unsigned int IndicesIndex_current = uvIndices[i];
    glm::vec2 uvz = temp_uvs[IndicesIndex_current-1];
    uvs.push_back(uvz);
  }

  for( unsigned int i=0; i<normalIndices.size(); i++ )
  {
      unsigned int normalIndex_current = normalIndices[i];
      glm::vec3 normz = temp_normals[normalIndex_current-1];
      normals.push_back(normz);
  }*/

}
  std::vector<unsigned int>* mesh_v_indices = new  std::vector<unsigned int>(vertexIndices);
  std::pair<std::vector<mesh_vertex>*,std::vector<unsigned int>*> vertex_pair_data = make_pair(mesh_v_prt,mesh_v_indices);
  return vertex_pair_data;
 //out_p_pack  = gen_parse_parket(vertices,normals,uvs);


}
};


class ply_parser
{
  public :
  void  open_read_file(std::string fname);
  size_t num_of_vertex_points()
  {
    return evt_vec.size();
  }

  size_t num_of_indices()
  {
    return e_indices_list.size();
  }
  void dump_data_terminal_at(int index)
  {
    element_vertex_tuple temp_evt = evt_vec.at(index);
    std::array<float,3> temp_vexcord = std::get<VERTEXZ3D>(temp_evt);
    std::cout << "vertexdata::" << temp_vexcord[0] << ':' << temp_vexcord[1] << ':'
            << temp_vexcord[2] <<'\n';
    }

  std::vector<float> return_vertex_xyz_data()
    {
      std::vector<float> temp_vertex_vec;
      for(size_t i =0; i<evt_vec.size(); i++)
      {
        element_vertex_tuple temp_evt = evt_vec.at(i);
        std::array<float,3> temp_vexcord = std::get<VERTEXZ3D>(temp_evt);
        temp_vertex_vec.push_back(temp_vexcord[0]);
        temp_vertex_vec.push_back(temp_vexcord[1]);
        temp_vertex_vec.push_back(temp_vexcord[2]);
      }
      return temp_vertex_vec;

    }
    std::vector<unsigned int> return_indices_data()
      {
        std::vector<unsigned int> temp_indices_vec;
        for(size_t i =0; i<e_indices_list.size(); i++)
        {
            std::array<unsigned int,4> temp_ind_array = e_indices_list.at(i);

          temp_indices_vec.push_back(temp_ind_array[0]);
          temp_indices_vec.push_back(temp_ind_array[1]);
          temp_indices_vec.push_back(temp_ind_array[2]);
          temp_indices_vec.push_back(temp_ind_array[3]);
        }
        return temp_indices_vec;

      }

  private :
  std::vector<element_vertex_tuple> evt_vec;
  std::vector<std::array<unsigned int,4>> e_indices_list;
};

class Wavefront_parser
{
  private :
  std::ifstream r_file;
  std::string raw_data;
  std::string line ="";
  int count_obj_num =0;
  std::vector<objs_tuplez> final_obj_list;
 public :
 size_t num_indicaez(int index)
 {
    objs_tuplez* temp_tuplez= &final_obj_list.at(index);
    std::vector<face>* temp_face_vec = &std::get<FACE_VEC_DATA>(*temp_tuplez);
    return temp_face_vec->size()*3;

 }
 objs_tuplez* return_tupled_ojk_at(int index)
 {
   return &final_obj_list.at(index);
 }

 std::vector<float> return_vertex_data_at(int index)
 {
   std::vector<float> vertx_data;
   objs_tuplez* temp_tuplez= &final_obj_list.at(index);
   std::vector<vertex_data>* temp_vertex_vec  = &std::get<VERTEX_VEC_DATA>(*temp_tuplez);

   for(size_t i =0; i< temp_vertex_vec->size(); i++)
   {

     vertex_data temp_vd = temp_vertex_vec->at(i);
     vertx_data.push_back(temp_vd.x);
     vertx_data.push_back(temp_vd.y);
     vertx_data.push_back(temp_vd.z);
     std::cout << "vertexloader::" << temp_vd.x <<':'<< temp_vd.y << ':'<< temp_vd.z <<'\n';
     /*
     vertx_data[i]   = temp_vd.x;
     vertx_data[i+1] = temp_vd.y;
     vertx_data[i+2] = temp_vd.z;
     */
   }

   return vertx_data;
 }

 std::vector<unsigned int> return_indices_data_at(int index)
 {
   objs_tuplez* temp_tuplez= &final_obj_list.at(index);
   std::vector<face>* temp_face_vec = &std::get<FACE_VEC_DATA>(*temp_tuplez);
   size_t num_ind =num_indicaez(index);
   unsigned int temp_indic_array[num_ind];
   size_t num_facez  = temp_face_vec->size();
   std::cout <<"num of faces::" << num_facez <<'\n';

   std::vector<unsigned int> temp_ind_dat;

   for(size_t i =0; i<num_facez; i++)
   {  face temp_face = temp_face_vec->at(i);

      for(size_t j =0; j< temp_face.indicesz_data.size(); j++)
      {

        indices_raw temp_indcraw = temp_face.indicesz_data[j];

        temp_ind_dat.push_back(temp_indcraw[0]);
        temp_ind_dat.push_back(temp_indcraw[1]);
        temp_ind_dat.push_back(temp_indcraw[2]);
      /*  temp_indic_array[i]   = temp_indcraw[0];
        temp_indic_array[i+1] = temp_indcraw[1];
        temp_indic_array[i+2] = temp_indcraw[2];
        std::cout << "data to load::" << temp_indcraw[0] << temp_indcraw[1]  << temp_indcraw[2] <<'\n';
        std::cout << "data loaded::" << temp_indic_array[i] << temp_indic_array[i+1]  << temp_indic_array[i+2] <<'\n';*/
      }

   }
   return temp_ind_dat;

 }

 size_t num_of_obj()
 {
   return final_obj_list.size();
 }
 void output_objdata()
 {
   for(size_t i = 0; i<final_obj_list.size(); i++ )
   {
     objs_tuplez temp_t =  final_obj_list.at(i);
     std::pair<std::string,int> temp_pair = std::get<1>(temp_t);
     std::vector<vertex_data> v_dat_vec =  std::get<2>(temp_t);
     std::vector<face> face_data =  std::get<3>(temp_t);

     std::cout << "object info:" << "index: " << std::get<0>(temp_t) << "  objtype:" << temp_pair.first
      << " objectnumber of that type::" << temp_pair.second << "\n";
      for(size_t k = 0; k<v_dat_vec.size(); k++ )
      {
        vertex_data temp_vd = v_dat_vec.at(k);
        std::cout << "  vertexdata:" << temp_vd.x << " " << temp_vd.y << " " <<  temp_vd.z << '\n';
      }
      for(size_t d = 0; d<face_data.size(); d++ )
      {   std::cout << "\nface::";
          face temp_face = face_data.at(d);
          for(size_t jk = 0; jk<temp_face.indicesz_data.size(); jk++)
          {
            indices_raw in_craw = temp_face.indicesz_data[jk];
            std::cout << " " << in_craw.indicez3[0] << " " << in_craw.indicez3[1] << " " << in_craw.indicez3[2] << '\n';
          }
      }
   }
 }
  void open_read_file(std::string fname)
  {
    r_file.open(fname,std::ios::in);
    std::string delimiter_name = ".";
    std::string delimiter_face ="/";
    bool is_more1 =false;

    if(r_file.is_open())
    {
      std::pair<std::string,int> current_obj;
      std::vector<vertex_data> vertex_list;
      std::vector<face> face_list;
      while(std::getline(r_file,line))
      {
        std::string line_flag;
        std::istringstream iss(line);
        iss >> line_flag;
        //std::cout << "getting lineflag" << line_flag <<'\n';
        if(line_flag == "o")
        {
          if(count_obj_num>0)
          {
            is_more1 = true;
            objs_tuplez cur_obj_t = std::make_tuple(count_obj_num,current_obj,vertex_list,face_list);
            final_obj_list.push_back(cur_obj_t);
            vertex_list.clear();
            face_list.clear();
          }

          count_obj_num++;
          std::cout <<"found a o" << '\n';
          std::string raw_name;
          iss >> raw_name;
          std::cout << "raw name:" << raw_name <<'\n';

          std::string obj_type;
          int obj_num;
          size_t pos =0;

          while((pos = raw_name.find(delimiter_name)) !=std::string::npos)
          {
            obj_type = raw_name.substr(0,pos);
            raw_name.erase(0,pos+delimiter_name.length());
            obj_num= std::stoi(raw_name);
          }

          current_obj = std::make_pair(obj_type,obj_num);
          std::cout <<obj_type << " " << obj_num;
        }

        if(line_flag == "v")
        {
          std::cout <<"found v";
          vertex_data v_dat;
          iss >> v_dat.x >> v_dat.y >> v_dat.z;
          vertex_list.push_back(v_dat);
        }

          if(line_flag == "f")
          {
            //std::cout << "found f";

            int pos = 0;
            indices_raw temp_indice_dat;
            std::string raw_face;
            face temp_face;
            int indic_raz;

            int ind_count = 0;

            std::vector<std::string> face_vec;
            while(!iss.eof())
            {
              iss >> raw_face;
              face_vec.push_back(raw_face);
            }

          //  std::cout << "\nrawface::" << raw_face;
            for(size_t v =0; v<face_vec.size(); v++)
            {       raw_face  = face_vec.at(v);
              while((pos = raw_face.find(delimiter_face)) !=std::string::npos)
              {

                indic_raz = std::stoi(raw_face.substr(0,pos));
              //  std::cout << "\n raw indicate::" << indic_raz << "\n";
                raw_face.erase(0,pos+delimiter_face.length());
                temp_indice_dat.indicez3[ind_count]=indic_raz;
                ind_count++;

                if(ind_count == 2)
                {
                  temp_indice_dat.indicez3[ind_count]=std::stoi(raw_face);
                //  std::cout << "face_compleated\n";
                  ind_count =0;
                  temp_face.indicesz_data.push_back(temp_indice_dat);
                }
              //  std::cout <<"remaning face::" << raw_face <<" what is count::"<<ind_count<< '\n';
              }
            }
            face_list.push_back(temp_face);
          }
      }
      r_file.close();

      if(is_more1 == false)
      {
        objs_tuplez cur_obj_t = std::make_tuple(count_obj_num,current_obj,vertex_list,face_list);
        final_obj_list.push_back(cur_obj_t);
      }
    }
    else
    {
      std::cerr <<"fakure to open file" << fname;
    }
  }
};
