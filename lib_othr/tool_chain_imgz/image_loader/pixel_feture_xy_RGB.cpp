//pixel_feture_xy_RGB.cpp


  #include "pixel_feture_xy_RGB.h"


  pixel_feture_xy_RGB::pixel_feture_xy_RGB()
    {
      pix_xy_fet[0]=-1;
      pix_xy_fet[1]=-1;
    }

// tuple feture pointer genrtz
  std::tuple<double,double,double>* pixel_feture_xy_RGB::getptr_channl_touple()
    {
      return &rgb_chanell_tuple;
    }

  void pixel_feture_xy_RGB::pcopyer(pixel_feture_xy_RGB pointfet)
    {
      rgb_chanell_tuple = pointfet.rgb_chanell_tuple;
      pix_xy_fet[0]= pointfet. pix_xy_fet[0];
      pix_xy_fet[1]= pointfet.pix_xy_fet[1];
    }
// maualty set point data
  void pixel_feture_xy_RGB::pmaual_feture_set(double x, double y,
                        double r,double g,double b)
    {
      rgb_chanell_tuple = std::make_tuple(r,g,b);
      pix_xy_fet[0]= x;
      pix_xy_fet[1]= y;
    }

//load image raw data to feture space
    void pixel_feture_xy_RGB::point_setter(RGB_pix_intzity* load_pix_intz, int x,int y)
      {


      //  std::cout << "->IN POINT_SETTER----pix-fet_xy_rgb"<< '\n';
          double red,green,blue;
          int Pix_id = (x*y)+y;

        //  std::cout << "row" << x<< "colmz" <<y << '\n'
            //        << "pixindez" <<  Pix_id << '\n' << '\n';

          //RGB_pix_intzity*  prt_instysturc = load_pix_intz.locat_pixel_fet_data(Pix_id);

          pix_xy_fet[0] = x;
          pix_xy_fet[1] = y;
          double(*intz_arry_ptr)[3];  //= new double();
          intz_arry_ptr =   &load_pix_intz->img_colour_intisity_double;

          red   = *intz_arry_ptr[0];
          green = *intz_arry_ptr[1];
          blue  = *intz_arry_ptr[2];

           rgb_chanell_tuple = std::make_tuple(red,green,blue);

      }

//summz
  void pixel_feture_xy_RGB::fetureaccumalor(pixel_feture_xy_RGB point_in)
  {
     pix_xy_fet[0] =+ point_in.pix_xy_fet[0];
     pix_xy_fet[1] =+ point_in.pix_xy_fet[1];

     std::get<0>(rgb_chanell_tuple) =+ std::get<0>(point_in.rgb_chanell_tuple);
     std::get<1>(rgb_chanell_tuple) =+ std::get<1>(point_in.rgb_chanell_tuple);
     std::get<2>(rgb_chanell_tuple) =+ std::get<2>(point_in.rgb_chanell_tuple);
     /*
     std::cout << "RGBaccumationz:R:" << std::get<0>(rgb_chanell_tuple)<<" G:"
          << std::get<1>(rgb_chanell_tuple)
          << " B:"<< std::get<2>(rgb_chanell_tuple)
          <<'\n';
          */
  }

  //ascalerr for whole intenizy
  void pixel_feture_xy_RGB::pointscaler(double scale)
    {
      pix_xy_fet[0]*=scale;
      pix_xy_fet[1]*=scale;
      std::get<0>(rgb_chanell_tuple)*=scale;
      std::get<1>(rgb_chanell_tuple)*=scale;
      std::get<2>(rgb_chanell_tuple)*=scale;
    }

  //feturespacecalulations
  double pixel_feture_xy_RGB::point_RGB_distance(pixel_feture_xy_RGB point_in)
    {
        return sqrt(
         (std::get<0>(rgb_chanell_tuple)-std::get<0>(point_in.rgb_chanell_tuple))*
         (std::get<0>(rgb_chanell_tuple)-std::get<0>(point_in.rgb_chanell_tuple))+

         (std::get<1>(rgb_chanell_tuple)-std::get<1>(point_in.rgb_chanell_tuple))*
         (std::get<1>(rgb_chanell_tuple)-std::get<1>(point_in.rgb_chanell_tuple))+

         (std::get<2>(rgb_chanell_tuple)-std::get<2>(point_in.rgb_chanell_tuple))*
         (std::get<2>(rgb_chanell_tuple)-std::get<2>(point_in.rgb_chanell_tuple))
         );
    }

  double pixel_feture_xy_RGB::point_spatial_distance(pixel_feture_xy_RGB point_in)
    {
      return sqrt(
        (pix_xy_fet[0]-point_in.pix_xy_fet[0])*(pix_xy_fet[0]-point_in.pix_xy_fet[0])+
        (pix_xy_fet[1]-point_in.pix_xy_fet[1])*(pix_xy_fet[1]-point_in.pix_xy_fet[1])
        );
    }
