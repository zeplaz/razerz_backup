#version 330 core

out vec4 Frag_colour;

in vec3 normal;
in vec3 frag_pos;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light_colour;
uniform vec3 object_colour;

void main()
{
  //ambient
  float ambient_strength = 0.1;
  vec3  ambient = ambient_strength*light_colour;

  //diffuse
  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(view_pos-frag_pos);
  float diff = max(dot(norm,light_dir),0.0);
  vec3 diffuse = diff*light_colour;

  //specular
  float specular_strength =0.5;
  vec3 view_dir = normalize(-light_dir,norm);
  vec3 reflect_dir = reflect(-light_dir,norm);
  float spec = pow(max(dot(view_dir,reflect_dir),0.0)32);
  vec3 specular = specular_strength*spec*light_colour;

  vec3 result = (ambient+diffuse+specular)*object_colour;
  Frag_colour = vec4(result,1.0);
}
