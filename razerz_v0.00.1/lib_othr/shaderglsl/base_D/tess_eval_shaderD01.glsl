#version 420
layout (quads,fractional_odd_spacing) in;
//layout (quads, equal_spacing, cw) in;
uniform sampler2D tex_displacement;

uniform
{
mat4 model_view_matrix;
mat4 proj_matrix;
uniform mat4 mvp;
float dmap_depth;

}

in out_TESS_CTL_SHADER{
  vec2 tess_uv;

} in_tess_evl_data;

out out_TESS_EVL_SHADER{
vec3 normal;
}out_tess_evl_data;
