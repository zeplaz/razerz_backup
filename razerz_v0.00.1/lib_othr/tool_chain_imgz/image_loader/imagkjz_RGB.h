

//img

#ifndef IMAGKJZ_H
#define IMAGKJZ_H

//libz
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>

#include "RGB_pix_intzity.h"
#include "pixel_feture_xy_RGB.h"
//  namespace image_realm {
//strucz? move to include?

struct Img_Header {
 std::string majic_numz ="";
 std::size_t  widthx=0;
 std::size_t  highty=0;
 std::uint32_t  rgb_max_intity = 255;
 };

class  imagkjz_RGB
{

    public :
     size_t img_size;
     std::vector<uint8_t> raw_img_rgb_vec;

    //loacl header imag struc
      Img_Header img_header;

    //mapstuff for feture locations
      std::unordered_map<int,RGB_pix_intzity> img_RGB_intzty_map;
      std::unordered_map<int,RGB_pix_intzity>::iterator incity_map_iter;

    public:
      void load_image_RGB(std::string);
      void write_image();
      void inilzatfeture_space();
      void set_feture_space(pixel_feture_xy_RGB*,int);
      RGB_pix_intzity* locat_pixel_fet_data(int id_pixloc);

//inlined funciosn..
  inline void set_pixel_raw_data()
  {
    for (incity_map_iter = img_RGB_intzty_map.begin();incity_map_iter != img_RGB_intzty_map.end(); incity_map_iter++)
    {
        RGB_pix_intzity temp_pix_intz  = incity_map_iter->second;
        uint8_t temp_array[3];
        temp_array[0]=(int) temp_pix_intz.img_colour_intisity_double[0];
        temp_array[1]=(int) temp_pix_intz.img_colour_intisity_double[1];
        temp_array[2]=(int) temp_pix_intz.img_colour_intisity_double[2];
        std::cout << "R:Raw doublez:" <<temp_pix_intz.img_colour_intisity_double[0] <<" to int: "<< temp_array[0]
                  << "tounchar:" << (uint8_t)temp_array[0] << '\n' <<'\n';
                  std::cout << "G:Raw doublez:" <<temp_pix_intz.img_colour_intisity_double[1] <<" to int: "<< temp_array[1]
                            << "tounchar:" << (uint8_t)temp_array[1] << '\n'<< '\n';
                            std::cout << "B:Raw doublez:" <<temp_pix_intz.img_colour_intisity_double[2] <<" to int: "<< temp_array[2]
                                      << "tounchar:" << (uint8_t)temp_array[2] << '\n'<< '\n';

        raw_img_rgb_vec.push_back((uint8_t)temp_array[0]);
        raw_img_rgb_vec.push_back((uint8_t)temp_array[1]);
        raw_img_rgb_vec.push_back((uint8_t)temp_array[2]);
    }
  }

    inline void write_head(std::ostream& out_stream)
       {
         out_stream << img_header.majic_numz << "\n"
                    << img_header.widthx << "\n"
                    << img_header.highty << "\n"
                    << img_header.rgb_max_intity << "\n";
       }


      inline Img_Header read_header(std:: fstream& instream)
        {

          Img_Header i_header = Img_Header{};
          instream >> i_header.majic_numz >> i_header.widthx >> i_header.highty
                   >>  i_header.rgb_max_intity;

          instream.ignore(256, '\n');
          std::cout << "hemajz:"<< i_header.majic_numz << '\n';
          std::cout << "hemajz:"<< i_header.widthx << '\n';
          std::cout << "hemajz:"<< i_header.highty << '\n';


          return i_header;
         }



       inline  void read_pix_rgb_raw(std::fstream& in_img_stream,
                                     std::vector<std::uint8_t>* const con_raw_pix_prt)
         {
           //std::vector<std::uint8_t>* const con_raw_pix_prt =&raw_img_rgb_vec;
            in_img_stream.read(reinterpret_cast<char*>(con_raw_pix_prt->data()),
                                con_raw_pix_prt->size());

            if(!in_img_stream)
            {
              printf("!@ERROR::datainticity read falure\n");
              std::cout <<con_raw_pix_prt->size();
            }
          }

    inline void write_raw_pix_data(std::fstream& out_strem, std::size_t const size)
      {
        //out_strem.write(reinterpret_cast<char* const*>(raw_pixdata),size);
        out_strem.write(reinterpret_cast<char*>(raw_img_rgb_vec.data()),size);
      }



};


#endif
