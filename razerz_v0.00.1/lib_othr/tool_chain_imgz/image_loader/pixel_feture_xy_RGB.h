

// pixel_feture_xy_RGB.h
#ifndef PIX_FET_XY_RGB_H
#define PIX_FET_XY_RGB_H

//std libz
#include <utility>
#include <tuple>
#include <math.h>
#include <iostream>

//localincluz
#include "RGB_pix_intzity.h"
//#include "imagkjz_RGB.h"

//declare used class
//  class imagkjz_RGB;


  class pixel_feture_xy_RGB
  {
    public:
    std::tuple<double,double,double> rgb_chanell_tuple;
    double pix_xy_fet[2];

    public :

    pixel_feture_xy_RGB();

    std::tuple<double,double,double>* getptr_channl_touple();

    void pcopyer(pixel_feture_xy_RGB);
    void pmaual_feture_set(double,double,double,double,double);
    void point_setter(RGB_pix_intzity*,int,int);
    void fetureaccumalor(pixel_feture_xy_RGB);
    void pointscaler(double);

    double point_RGB_distance(pixel_feture_xy_RGB);
    double point_spatial_distance(pixel_feture_xy_RGB);
};

#endif
