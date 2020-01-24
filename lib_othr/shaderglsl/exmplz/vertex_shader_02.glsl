#version 430

in layout(location=0) vec4 vertex_position_model;
in layout(location=1) vec4 vertex_colour;
in layout(location=2) vec3 vertex_normal;
in layout(location=3) vec4 vertex_light_alphaz;

uniform mat4 model_to_projection_mat;
uniform mat4 model_to_world_matrix;

out vec3 normal_world;
out vec3 vertex_pos_world;
out vec4 vertex_to_frag_colour;
//alpha deffuse,alphaspecular,tightness_spec
out vec4 vertex_to_frag_light_modfierz;
void main()
{
	gl_Position = model_to_projection_mat*vertex_position_model;
	normal_world =vec3(model_to_world_matrix*vec4(normal_world,0));
	vertex_pos_world = vec3(model_to_world_matrix*vertex_position_model);
	vertex_to_frag_colour = vertex_colour;
}
