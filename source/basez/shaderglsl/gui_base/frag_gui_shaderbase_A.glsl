#version 450
layout (location = 0) in vec4 vertex_pos_tex; //two vec2z

in vec2 out_texture_cordz;

out vec4 frag_colour;

uniform sampler2D utext_samp;
uniform vec4 ucolour;

uniform mat4 proj;
void main {
  vec4 text_samp =vec4(1.0,1.0,1.0,texture(utext_samp,out_texture_cordz).r); 
}
//layout(location = 0)  attr_text_texture;
