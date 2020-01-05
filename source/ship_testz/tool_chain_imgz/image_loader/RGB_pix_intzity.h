#ifndef RGB_PIX_INTZITY_H
#define RGB_PIX_INTZITY_H
//RGB_pix_intzity.h
/*
template <class type>
inline type derefrence_type(void * ptr)
{
return *(type*)(ptr);
}
*/

 struct RGB_pix_intzity{

  double img_colour_intisity_double[3];
  uint16_t colour_rgb_Raw[3];

  RGB_pix_intzity(double,uint16_t);
  RGB_pix_intzity()
  {
    img_colour_intisity_double[0]= 0;
    img_colour_intisity_double[1]= 0;
    img_colour_intisity_double[2]= 0;
    colour_rgb_Raw[0]=0;
    colour_rgb_Raw[1]=0;
    colour_rgb_Raw[2]=0;
  }
};

#endif
