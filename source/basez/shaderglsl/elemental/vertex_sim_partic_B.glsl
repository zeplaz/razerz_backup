#version 420 core

uniform mat4 model_matrix;
uniform mat4 proj_matrix;
uniform int  triangle_count;

layout (location =0) in vec4 pos;
layout (location =1) in vec3 velocity;


out OUT_VS{
  vec4 pos_out;
  vec3 velocity_out;
} out_vs;

uniform  samplerBuffer geo_tbo;
uniform float time_step = 0.02;







vec3 reflect_vector(vec3 v,vec3 n)
{
  return v-2.0*dot(v,n)*n;
}


bool intersect(vec3 origin,vec3 direction,vec3 v0,vec3 v1,vec3 v2, out vec3 point)
{

  vec3 u,v,n;
  vec3 w0,w;
  float r,a,b;

  u = (v1-v0);
  v = (v2-v0);
  n =cross(u,v);


  w0 = origin - v0;
  a  = -dot(n,w0);
  b  = dot(n,direction);

  r = a/b;
  point= origin+r*direction;

  if( r<0.0 || r>1.0)
  {
    return false;
  }

  float uu,uv,vv,vu,wu,wv,D;

  uu =dot(u,u);
  uv = dot(u,v);
  vv =dot(v,v);
  v  = point-v0;
  wu =dot(w,u);
  wv = dot(w,v);

  D = uv*uv-uu*vv;

  float a,t;
  s=(uv*wv-vv*wu)/D;

  t =(uv*wu-uu*wv)/D;
  if(s<0.0||s>1.0)
  return false;

  r=(uv*wu-uu*wv)/D;
  if(t<0.0 || (s+t)>1.0)
  return false;

  return true;
}
