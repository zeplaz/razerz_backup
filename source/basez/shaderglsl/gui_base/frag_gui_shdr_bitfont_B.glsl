#version 450
layout (origin_upper_left)  in vec4 gl_FragCoord; //two vec2z

layout(location = 0)  out vec4 frag_colour;

//charmap
layout (binding =0) uniform isampler2D text_buff;

//font
layout (binding =1) uniform isampler2DArray font_texture;


void main(void)
{

  ivec2 frag_cord   = ivec2(gl_FragCoord.xy);
  ivec2 char_size   = textureSize(font_texture,0).xy;
  ivec2 char_loc    = frag_cord / char_size;
  ivec2 textel_cord = fragcord % char_size;

  int active_char   =  texelFetch(text_buff,char_loc,0).x;

  float val = texelFetch(font_texture,ivec3(textel_cord,active_char),0).x;

  if(val ==0.0)
  discard;
  frag_colour = vec4(0.2,1.0,0.3,1.0);
}
