#version 430
layout (points) in;
layout(triangle_strip,max_vertices = 8) out;

in vec3 base_colour[];
out vec3 frag_colour;
