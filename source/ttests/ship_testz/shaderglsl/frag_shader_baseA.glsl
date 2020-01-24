#version 430 core
//out vec4 FragColor;
//out vec3 FragColor;
out vec4 FragColor4;
in vec2 UV;

uniform sampler2D myTextureSampler;
vec4 base_colour = vec4(0.f,0.f,1.f,1.f);
void main()
{
    //FragColor = vertexColor*ourColor;
    //FragColor4 = base_colour;
    FragColor4 = texture( myTextureSampler, UV );
}
