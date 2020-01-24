
// imagkjz_RGB.cpp

#include "imagkjz_RGB.h"

    void imagkjz_RGB::load_image_RGB(std::string filename)
     {
        std::fstream image_fileb_stream;

        image_fileb_stream.open(filename,std::fstream::in | std::ios::binary);

        Img_Header tmp_im_head = imagkjz_RGB::read_header(image_fileb_stream);
        img_header= tmp_im_head;

        raw_img_rgb_vec.resize((img_header.widthx)*(img_header.highty)*3);
        char* buffer = new char [raw_img_rgb_vec.size()];

        //pixel_raw_RGB->resize((img_header.widthx)*(img_header.highty)*3);
        img_size = img_header.widthx*img_header.highty;

        std::cout << "size from hedz"<< img_header.widthx*img_header.highty <<'\n';

        image_fileb_stream.read(buffer,raw_img_rgb_vec.size());

        for(size_t ims =0; ims< raw_img_rgb_vec.size(); ims++)
        {
          int pos=0;
          raw_img_rgb_vec.at(ims)= (int)(buffer[ims]);
          pos++;
        }

          if(!image_fileb_stream)
            {
             printf("!@ERROR::datainticity read falure \n");
             std::cout <<raw_img_rgb_vec.size();
            }
            else
            {
              printf("FILE LOADED SUCESSFULLY!:)..onehopez \n");
            }
          image_fileb_stream.close();
      }


      void imagkjz_RGB::write_image()
       {
         std::string file_img_name;
         uint8_t const* pixdata[(img_header.widthx)*(img_header.highty)*3];
        // pixdata.resize();
         //pixdata = (uint8_t)

         Img_Header out_header = Img_Header{};
         out_header.majic_numz = "P6";
         out_header.widthx = img_header.widthx;
         out_header.highty = img_header.highty;

         std::cout << "Enter FILE OUTNAME:" <<"\n";
         std::cin >> file_img_name;
         std::fstream outfile_strm_img;

         outfile_strm_img.open("output/"+ file_img_name + "_outim.ppm",std::fstream::out|std::ios::binary);


         write_head(outfile_strm_img);
         write_raw_pix_data(outfile_strm_img, raw_img_rgb_vec.size() );
         outfile_strm_img.close();
       }

       void imagkjz_RGB::set_feture_space(pixel_feture_xy_RGB* in_pix_fet,int id_in)
        {
          RGB_pix_intzity  temp_RGB_inxzy;
          temp_RGB_inxzy.img_colour_intisity_double[0]= std::get<0>(in_pix_fet->rgb_chanell_tuple);
          temp_RGB_inxzy.img_colour_intisity_double[1]= std::get<1>(in_pix_fet->rgb_chanell_tuple);
          temp_RGB_inxzy.img_colour_intisity_double[2]= std::get<2>(in_pix_fet->rgb_chanell_tuple);

        //  pixel_feture_xy_RGB temp_space = *in_pix_fet;

         img_RGB_intzty_map.insert(std::make_pair(id_in,temp_RGB_inxzy));
        }

      void imagkjz_RGB::inilzatfeture_space()
        {

            for(int Pix_id=0; Pix_id<raw_img_rgb_vec.size()-3;Pix_id++)
            {
            //  std::cout << "mixrawzie:" << raw_img_rgb_vec.size() << '\n'
          //    << "pix_locz:" << Pix_id << '\n';

              RGB_pix_intzity image_intcity_struc;
            //.image_intcity_struc.colour_rgb_Raw
              image_intcity_struc.img_colour_intisity_double[0] = (double)(raw_img_rgb_vec.at(Pix_id));
              image_intcity_struc.img_colour_intisity_double[1]=  (double)(raw_img_rgb_vec.at(Pix_id+1));
              image_intcity_struc.img_colour_intisity_double[2]=  (double)(raw_img_rgb_vec.at(Pix_id+2));
            //  std::cout <<"-->INEZXITY_SPACE____" << '\n' << ":->new pixel at:" << Pix_id << '\n'
            //            << "with inxzty xyz:" <<image_intcity_struc.img_colour_intisity_double[0] << " "
            //            <<image_intcity_struc.img_colour_intisity_double[1] << " "
          //              <<image_intcity_struc.img_colour_intisity_double[2] << '\n' << '\n';

              //std::make_pair(Pix_id,image_intcity_struc);
              img_RGB_intzty_map.insert(std::make_pair(Pix_id,image_intcity_struc));
            }
            //reinterpret_cast<uint16_t>
         }

       RGB_pix_intzity* imagkjz_RGB::locat_pixel_fet_data(int id_pixloc)
         {
            incity_map_iter = img_RGB_intzty_map.find(id_pixloc);

            if(incity_map_iter==img_RGB_intzty_map.end())
              {
                printf("||_NOTFOUND_DATA_ORPIXEL UKNOWN>\n");
                return nullptr;
              }

         else {
                RGB_pix_intzity* prr_tempz_inxz = &incity_map_iter->second;
                return (prr_tempz_inxz);
              }
         }
