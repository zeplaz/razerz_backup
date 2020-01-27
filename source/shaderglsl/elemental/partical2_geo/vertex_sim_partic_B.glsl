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
uniform vec3 accelleration;

flat float reflect_vel_modifer = 0.8;
flat float y_bounds  = -100.0;
flat vec3 velo_bound = vec3(0.2,0.1,-0.3)

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

  if( r < 0.0 || r > 1.0)
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
  if( s< 0.0 || s > 1.0)
  return false;

  r=(uv*wu-uu*wv)/D;
  if(t<0.0 || (s+t)>1.0)
  return false;

  return true;
}


void main(void)
{
  vec3 new_velocity = velocity+ accelleration*time_step;
  vec4 new_pos      = pos+vec4(new_velocity*time_step,0.0);
  vec3 v0,v1,v2;
  vec3 point;
  int i;
  for(i=0;i<triangle_count;i++)
  {
    v0=texelFetch(geo_tbo,i*3).xyz;
    v1=texelFetch(geo_tbo,i*3+1).xyz;
    v2=texelFetch(geo_tbo,i*3+2).xyz;
    if(intersect(pos.xyz,pos.xyz-new_pos.xyz,v0,v1,v2,point))
    {
      vec3 n = normalize(cross(v1-v0,v2-v0));
      new_pos = vec4(point+reflect_vector(new_pos.xyz-point,n),1.0);
      new_velocity = reflect_vel_modifer*reflect_vector(new_velocity,n);
    }
  }
  if(new_pos<y_bounds)
  {
    new_pos = vec4(-new_pos.x*0.3,pos.y+80.0,0.0,1.0);
    new_velocity*=velo_bound;
  }

  velocity_out= new_velocity*0.9999;
  pos_out     = new_pos;
  gl_Position = proj_matrix*(model_matrix*pos);
}
