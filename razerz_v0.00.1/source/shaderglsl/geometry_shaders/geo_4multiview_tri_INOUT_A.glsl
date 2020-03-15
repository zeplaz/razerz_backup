#version 430 core

layout (triangles, invocations = 1) in;
layout(triangle_strip, max_vertices =3) out;


uniform int viewport_index;

in VS_OUT{
  vec2 v_uv;
  vec3 v_normal;
  vec4 v_colour;
} gs_in[];

out GS_OUT{
  vec2 v_uv;
  vec3 v_normal;
  vec4 v_colour;
} gs_out;

void main(void)
{

  gl_Position    = gl_Position[viewport_index];
  gl_out.v_uv    = gs_in.v_colour[viewport_index];
  gl_out.v_normal= gs_in.v_normal[viewport_index];
  gl_out.v_colour= gs_in.v_uv[viewport_index];

  gl_ViewportIndex = viewport_index;
  EmitVertex();
  EndPrimitive();
}
