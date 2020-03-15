#version 450 core

flat int  FLOC_MEM_BIDN_INDX = 1;
flat int  FLOC_MEM_BIDN_INDX = 2;
flat int  PARTCL_UNI_BIDN_INDX = 3;
flat int  PARTCL_U_VELOC_INDEX =4;
flat int  PARTCL_U_POS_INDEX =5;
//orginze intow two subrunties thus can batch commute calls.
flat int OBJK_PATICZ_REAL;
/*
//floc
layout (local_size_x = ) in;

uniform float[MAXRULE] rule_array;
vec4 goal;
float timesteps;

layout(std430 binding = FLOC_MEM_BIDN_INDX) buffer floc_mem_in
{
  unit_mem umem[];
} floc_in_data;

layout(std430 binding = FLOC_MEM_BIDN_INDX) buffer floc_mem_out
{
  unit_mem umem[];
} floc_out_data;

*/
//end floc

const int MAX_PARTC_ATTACTOR = 64;

layout(std140,binding =PARTCL_UNI_BIDN_INDX) uniform attached_bock
{
  vec4 partc_attractor[MAX_PARTC_ATTACTOR];//xyz and w used as mass? why 64?
};
layout (local_size_x = 1024) in;

layout(rgba32f, binding  = PARTCL_U_VELOC_INDEX) uniform imagebuffer velocity_buffer;
layout(rgba32f, binding  = PARTCL_U_POS_INDEX)   uniform imagebuffer pos_buffer;

uniform float dt;

  void partical_func (){
  vec4 val = imageload(velocity_buffer,int(gl_GlobalInvocationID.x));
  vec4 pos = imageload(pos_buffer,int(gl_GlobalInvocationID.x));

  int i;

  pos.xyz += val.xyz*dt;
  pos.w   -= 0.0001*dt;

  for(i=0;i<4;i++)
  {
    vec3 dist = (partc_attractor[i].xyz-pos.xyz);
    val.xyz +=dt*dt*partc_attractor[i].w*normalize(dist)/(dot(dist,dist)+10.0);
  }

  if(pos.w<=0.0)
  {
    pos.xyz  = -pos.xyz*0.1;
    val.xyz *= 0.01;
    pos.w   += 1.0f;
  }

  imagestore(pos_buffer, int(gl_GlobalInvocationID.x),pos);
  imagestore(velocity_buffer,int(gl_GlobalInvocationID.x),val);
}

void main(void)
{
  partical_func ();
}
