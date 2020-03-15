#version 450 core

layout(location = 0) out vec4 FINAL_colour;
//layout (location//setframebuf i want depth, and intienziy)

in SENT_TO_FRAG{
vec4  pass_colour;
vec4 pass_light;

}in_pip_dat;

struct ray
{
vec4 origin;
vec3 drection;
}

struct cube {
vec4 bvex[8];
}
//is it an opximation to place radius as w?
struct sphere {
  vec3 center;
  float radius;
}


float intersect_ray_convex(ray in_ray, sphere in_convec, out vec4 hit_pos, out vec3 normal)
{

}

float intersect_ray_plane(ray in_ray, sphere in_convec, out vec4 hit_pos, out vec3 normal)
{

}

float intersect_ray_sphere(ray in_ray, sphere in_shpere, out vec4 hit_pos, out vec3 normal)
{
  vec3 centriod = in_ray.origin - in_shpere.center;
  float qud_formB = 2.0 * dot(in_ray.drection,centriod);
  float qud_formC = dot(centriod,centriod)-in_shpere.radius*shpere.radius;
  float qud_formB2 = qud_formBB+qud_formB

  float under_qresult = qud_formB2-4.0*qud_formC;

  if(under_qresult<0.0)
  return 0.0;
}

float float intersect_ray_cube(ray in_ray, cube in_cube, out vec4 hit_pos, out vec3 normal)

{

}
void main(void)
{

  //for particals.
  #ifdef fr_park
FINAL_colour = mix(mix(in_pip_dat.pass_light,intensity),pass_colour);
#endif fr_park


//forrayz.


  //for partidcalend
}
