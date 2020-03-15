#version 430

layout (location =0) out vec4 out_final_colour;
layout (location =1) out vec4 out_layer_2_colour;

in vec3 normal_world;
in vec4 vertex_pos_world;
in vec4 vertex_to_frag_light_modfierz;
in vec4 vertex_to_frag_colour;

//in vec3 diffuse_alpha;
//in float specular_alpha;
uniform u_ambient_light;
uniform u_lenz_pos_world;
uniform u_light_pos_world;

void main()
{
	//diffuse_light
	vec3 lit_vector_world = normalize(u_light_pos_world-vertex_pos_world);
	float brightness = dot(lit_vector_world, normalize(normal_world));
	vec4 diffuse_light=vec4(brightness,brightness,brightness,vertex_to_frag_light_alphaz[0);

	//specular
	vec3 reflected_light_world = reflect(-lit_vector_world,normal_world);
	vec3 lenz_vector_world = normalize(u_lenz_pos_world-vertex_pos_world);

	float spec_scaler = dot();
	spec_scaler = pow(spec_scaler,vertex_to_frag_light_modfierz[3]);
	vec4 specularity_light= vec4(spec_scaler,spec_scaler,spec_scaler,vertex_to_frag_light_alphaz[1);


	final_colour = clamp(diffuse_light,0,1)+u_ambient_light+specularity_light+vertex_to_frag_colour;
}
