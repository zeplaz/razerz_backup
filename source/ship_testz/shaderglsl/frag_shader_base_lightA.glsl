#version 330 core

out vec4 Frag_colour;

in vec3 base_light_colour;

uniform object_colour;

void main()
{
  Frag_colour = vec4(base_light_colour*object_colour,1.0);
}
