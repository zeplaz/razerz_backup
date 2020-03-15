#version 430 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout(location = 1) in vec3 anormalz;
layout(location = 2) in vec2 vertexUV;

//out vec4 vs_pos_world;
out vec2 UV;

uniform mat4 model_view_projection;


void main()
{   //vs_pos_world = vec4(model_matrix*vec4(aPos,1.f)).xyz;

    gl_Position = model_view_projection*vec4(aPos,1.0f);  //see how we directly give a vec3 to vec4's constructor
    UV = vertexUV;
}
