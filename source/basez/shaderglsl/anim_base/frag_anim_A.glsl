#version 450



in VERTEX_SHADR_OUT
{
  vec2 v_uv;
  vec3 v_normal;
  vec4 v_colour;
} in_vrx;

out vec4 fColor;

uniform sampler2D texUnit;

void main()
{
     //vec4 texcolor = texture2D(texUnit,coords0);

     fColor = v_colour;
}
