#version 430
layout (vertices =16) out;

const int AB =2;
const int BC =3;
const int CD =0;
const int DA =1;

uniform int tess_fractor;
uniform float tess_slope;
uniform tess_shift;

uniform vec3 lenz_pos;

float cal_tess_level(float dist)
{
  float tess_levl = max(0.0,tess_fractor/pow(tess_slope+tess_shift));
  return tess_levl;
}


void main()
{



  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
