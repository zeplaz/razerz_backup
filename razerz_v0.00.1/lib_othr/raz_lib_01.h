


static const float inch_to_mm =25.4;

struct screen_space_pramz
{
  float screen_aperture_width;
  float screen_aperture_hight;

  float focus_length;
  float screen_aspect_ratio;
  float near_clip_plane;

} scr_sp_prm, *scr_sp_prm;


//FoV
float FoV(float fAwidth,float fAhight, float focalLength)
{
  return 2*180/M_PI *atan((fAwidth*inch_to_mm/2)/focalLength);
}
