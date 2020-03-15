#version 420 core

uniform mat4 model_matrix;
uniform mat4 proj_matrix;

layout (location=0) in vec4 pos;
layout (location=1) in vec3 normal;

out OUT_VS{
  vec4 world_space_pos;
  vec3 vs_fs_normal;
} out_vs;


void main(void)
{
  vec4 pos =(model_matrix*(pos*vec4(1.0,1.0,1.0,1.0)));
  out_vs.world_space_pos=pos;
  out_vs.vs_fs_normal=normalize((model_matrix*vec4(normal,0.0)).xyz);
  gl_Position = proj_matrix*pos;
}
