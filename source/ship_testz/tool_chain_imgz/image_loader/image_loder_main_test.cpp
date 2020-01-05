#include "imagkjz_RGB.h"
//#include "meanshift_3rdparty/MeanShift.h"


/*void nabour_smoother(imagkjz_RGB& in_image)
{
  unsigned int total_pixelz = n_image.img_header.widthx*in_image.img_header.highty;
  uint8_t n0,n1,n2,n3,n4,n5,n6,n7, n8;

  for(unsigned int i =0; i<total_pixelz; i++)
  {

  }
  in_image.img_header.widthx;
  in_image.img_header.highty;
  in_image.raw_img_rgb_vec;
}*/

std::vector<std::vector<double>> convert_tovecvecduble(imagkjz_RGB& in_img)
{

  std::vector<std::vector<double>> image_dublez;
  unsigned int total_pix = in_img.img_header.widthx * in_img.img_header.highty;
  for(unsigned int i =0;i<total_pix;i++ )
  {
      std::cout <<  in_img.raw_img_rgb_vec.at(i);
      if(i%64==0)
      {
        std::cout << '\n';
      }
  }

  for(unsigned int i = 0; i<in_img.img_header.highty; i++)
{
  std::vector<double> row;
  for(unsigned int j = 0; j<in_img.img_header.widthx; j++)
  {
    std::cout <<  in_img.raw_img_rgb_vec.at(j);
    //std::cout << "value in::" << in_img.raw_img_rgb_vec.at(j)<<'\n';
    double temp_conver_val =(double)(in_img.raw_img_rgb_vec.at(j));
  //  std::cout <<"value double::" <<temp_conver_val << '\n';
    row.push_back(temp_conver_val);
  }
  std::cout<< '\n';
  image_dublez.push_back(row);
}
return image_dublez;
}

std::vector<double> convert_vecduble(imagkjz_RGB& in_img)
{

  std::vector<double> image_dublez;

  unsigned int total_pix = in_img.img_header.widthx * in_img.img_header.highty;

  for(unsigned int i = 0; i<total_pix; i++)
  {
    double temp_conver_val =(double)(in_img.raw_img_rgb_vec.at(i));
    std::cout << temp_conver_val;
    if(i%64==0)
    {
      '\n';
    }
     image_dublez.push_back(temp_conver_val);
  }

return image_dublez;
}

imagkjz_RGB convertvec_toRGB(std::vector<double> shift_img)
{
 imagkjz_RGB new_image;
 for(size_t i=0; i<shift_img.size();i++)
 {
   double tempdubz;
   tempdubz = shift_img.at(i);
   uint8_t pixelval= (uint8_t)tempdubz;
    new_image.raw_img_rgb_vec.push_back(pixelval);

 }
 return new_image;
}


 imagkjz_RGB convertvecvec_toRGB(std::vector<std::vector<double>> shift_img)
{
  imagkjz_RGB new_image;
  for(size_t i=0; i<shift_img.size();i++)
  {
    std::vector<double> tempdubz;
    tempdubz = shift_img.at(i);
    for(size_t j=0; j<tempdubz.size(); j++)
    {
          uint8_t pixelval= static_cast<uint8_t> (tempdubz.at(j));
       new_image.raw_img_rgb_vec.push_back(pixelval);
    }
  }
  return new_image;
}
double euclidean_distance(const std::vector<double> &point_a, const std::vector<double> &point_b){
    double total = 0;
    for(int i=0; i<point_a.size(); i++){
        const double temp = (point_a[i] - point_b[i]);
        total += temp*temp;
    }
    return sqrt(total);
}

double euclidean_distance_sqr(const std::vector<double> &point_a, const std::vector<double> &point_b){
    double total = 0;
    std::cout <<"ecludadistazzz size point a::" <<  point_a.size() << '\n';

    for(int i=0; i<point_a.size(); i++){
        std::cout << "point a:" << point_a[i] <<"::pointb::"<<point_b[i] <<'\n';
        const double temp = (point_a[i] - point_b[i]);
        total += temp*temp;
    }
    return (total);
}

double gaussian_kernel(double distance, double kernel_bandwidth){
  std::cout <<"gauzekrrnal\n";
    double temp =  exp(-1.0/2.0 * (distance*distance) / (kernel_bandwidth*kernel_bandwidth));
    return temp;
}

int main(int argc, char* argv[])

  {
    imagkjz_RGB in_image;
    imagkjz_RGB shifted_image;
    in_image.load_image_RGB("cmd_coven_text_01.ppm");

    in_image.img_header.widthx;
    in_image.img_header.highty;
    in_image.inilzatfeture_space();
    std::vector<double> img_duble  = convert_vecduble(in_image);
    std::vector<std::vector<double>>  double_image;

    /*for(unsigned int i = 0; i<img_duble.size();i++)
    {
      std::vector<double> rowz;
      for(unsigned int j =0; j<64;j++)
      {

      }
      double_image.push_back()
    }*/
     double_image = convert_tovecvecduble(in_image);

    for(size_t i=1; i<double_image.size()-1;i++)
    {
        double diz = euclidean_distance_sqr(double_image.at(i-1),double_image.at(i+1));
        double gauz = gaussian_kernel(diz,2);
        std::cout << "diz::" << diz << ":::gauz::" <<gauz <<'\n';
    }

    //std::cout << "size lagervec::" << double_image.size() <<'\n';

    //std::vector<MeanShift::Point> vec_pointz =static_cast<std::vector<MeanShift::Point>> (double_image);
    //MeanShift *ms = new MeanShift(NULL);
    //MeanShift::Point p_img =img_duble;
    double kernal_band = 2;
  //  shifted_image=   convertvecvec_toRGB(double_image);
     shifted_image=   convertvec_toRGB(img_duble);
    shifted_image.write_image();

    //std::cout <<"begin ms\n";


    //std::vector<Cluster> clusters = ms->cluster(double_image,kernal_band);

    //MeanShift::Point shifted_pointz = ms->meanshift(vec_pointz,kernal_band);
    //std::cout <<"numm of cluserz::" << clusters.size() <<'\n';
    //shifted_image = convertvec_toRGB(clusters.shifted_points);
    //in_image.set_pixel_raw_data();



  //  in_image.write_image();


  return 0;
}


/*
    for(size_t i=0; i<double_image.size();i++)
    {
      std::vector<double> tempdubz;
      tempdubz = double_image.at(i);
      for(size_t j=0; j<tempdubz.size(); j++)
      {
        std::cout << "doubleval" << tempdubz.at(j);
      }
    }*/
