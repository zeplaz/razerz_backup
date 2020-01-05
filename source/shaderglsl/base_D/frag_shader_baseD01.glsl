#version 450 core


out vec4 final_colour;

in out_VERTEX_SHADER{
  vec3 view;
  vec2 frag_uv;
  vec3 frag_normal;
  vec4 frag_pos;
  vec3 vertx_lenz_VM;
}in_frag_data;
