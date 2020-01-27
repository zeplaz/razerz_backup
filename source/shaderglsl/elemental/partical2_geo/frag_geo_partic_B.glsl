#version 430 core

layout (location =0) out vec4 colour;
in vec3 vs_fs_normal;

vec4 ambient_c = vec4(0.2,0.4,0.3,1.0);
vec4 defuse_c = vec4(0.4,0.4,0.4,1.0);
vec4 spec_c   = vec4(0.8,0.5,0.2,1.0);
float shinyness = 70.0;

void main(void)
{
  colour = ambient_c+defuse_c*abs(vs_fs_normal)+spec_c*pow(abs(vs_fs_normal.z),shinyness);
}
