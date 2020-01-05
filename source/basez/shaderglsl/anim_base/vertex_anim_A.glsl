#version 450

layout(location = 0) in vec3 position;

layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 tangents;
layout(location = 4) in vec4 colour;

layout(location = 5) in ivec4 jointIDs;
layout(location = 6) in vec4 weights;

layout(location = 7) in int meterialID;


out VERTEX_SHADR_OUT
{
  vec2 v_uv;
  vec3 v_normal;
  vec4 v_colour;
} out_vrx;

const int MAX_JOINTZ = 100;

uniform mat4 u_jonts[MAX_BONES];
uniform mat4 MMatrix;
uniform mat4 VPMatrix;
uniform mat3 normal_matrix;

void main ()
{
      out_vrx.v_normal=normalize(normal_matrix*vec4(position,1.0f));
      out_vrx.v_colour = colour;

     mat4 BMatrix =  a_jonts[jointIDs[0]] * weights[0];
          BMatrix += a_jonts[jointIDs[1]] * weights[1];
          BMatrix += a_jonts[jointIDs[2]] * weights[2];
          BMatrix += a_jonts[jointIDs[3]] * weights[3];

     gl_Position = VPMatrix * MMatrix * BMatrix * vec4(position,1.0f));

     out_vrx.v_uv = uv;

}
