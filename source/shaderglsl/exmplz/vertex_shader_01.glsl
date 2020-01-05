#version 430

in layout(location=0) vec3 positions;
in layout(location =1) vec4 vertexColour;

uniform mat4 final_proj_matrix;
out vec4 the_colour_tofrag;

void main()
{
	vec4 v = vec4(positions,1.0);
	gl_Position = final_proj_matrix*v;
	the_colour_tofrag = vertexColour;

}
