


void glPatchParameteri(GLenum pname​​, GLint value​​);(GL_PATCH_VERTICES)
gl_NormalMatrix();
 void glBindTextureUnit(GLuint unit​, GLuint texture​); //Requires GL 4.5 or ARB_direct_state_access

 void glPatchParameterfv(GLenum pname​​, const GLfloat *values​​);

 When pname​ is GL_PATCH_DEFAULT_OUTER_LEVEL, values​ is a 4-element array of floats defining the four outer tessellation levels. When pname​ is GL_PATCH_DEFAULT_INNER_LEVEL, values​ is a 2-element array of floats defining the two inner tessellation levels.
 ivec textureSize(gsampler sampler​, int lod​);
  int textureQueryLevels(gsampler sampler​);
   gvec textureProj(gsampler sampler​, vec projTexCoord​[, float bias​]);


  gvec texture(gsampler sampler​, vec texCoord​[, float bias​]);

This samples the texture given by sampler​, at the location texCoord​, with an optional LOD bias value of bias​. For sampler types that cannot have LODs, the bias​ parameter cannot be used.

Sampling from shadow samplers return a "float", representing the result of the comparison. Sampling from other kinds of samplers returns a gvec4, matching the type of gsampler. This function does not work with multisample or buffer samplers.


vertex shader

The built-in variables specific to the vertx shader are listed in the table below. They are listed as input and out variables. The input variables are given values by the OpenGL pipeline before your vertex shader. The output variables should be given values by the shader you write.
output	qualifier	function
vec4 gl_Position		vertex shader writes to this variable to pass on the new value for the current vertex
float gl_PointSize		vertex shader writes to this variable to pass on the new value for the current point sizein pixels

fragment shader

Like the vertex shader the fragment shader can recieve values alreadyin the OpenGL pipeline and write values back to the pipeline. The variables with qualifiers varying are derived from the varying variables of the vertex shader.
input	qualifier	function
vec4 gl_FragCoord		read-only current fragment window relative coordinate. z is 0-1 and assigned to gl_FragDepth if no other value is assigned.
bool gl_FrontFacing		true if the fragment belongs to a front facing geometric primitive.
int gl_PointCoord		fragment position within a point (point rasterization only)in the range 0.0 to 1.0
output	qualifier	function
vec4 gl_FragColor		the colour of the fragment
vec4 gl_FragData		data associated with the fragment
is an array of data that can be used by the rest of the pipeline.
If you assign a value to gl_FragData then you most not assign a value to
gl_FragColor and visa versa.
vector types	function
sampler1D	used to access to 1D texture
sampler2D	used to access to 2D texture
sampler3D	used to access to 3D texture
samplerCube	used to access to cube-mapped texture
sampler1DShadow	used to access a 1D shadow map
sampler2DShadow	used to access a 2D shadow map

gsampler1D 	GL_TEXTURE_1D 	1D texture
gsampler2D 	GL_TEXTURE_2D 	2D texture
gsampler3D 	GL_TEXTURE_3D 	3D texture
gsamplerCube 	GL_TEXTURE_CUBE_MAP 	Cubemap Texture
gsampler2DRect 	GL_TEXTURE_RECTANGLE 	Rectangle Texture
gsampler1DArray 	GL_TEXTURE_1D_ARRAY 	1D Array Texture
gsampler2DArray 	GL_TEXTURE_2D_ARRAY 	2D Array Texture
gsamplerCubeArray 	GL_TEXTURE_CUBE_MAP_ARRAY 	Cubemap Array Texture
(requires GL 4.0 or ARB_texture_cube_map_array)
gsamplerBuffer 	GL_TEXTURE_BUFFER 	Buffer Texture
gsampler2DMS 	GL_TEXTURE_2D_MULTISAMPLE 	Multisample Texture
gsampler2DMSArray 	GL_TEXTURE_2D_MULTISAMPLE_ARRAY 	Multisample Array Texture
sampler1DShadow 	GL_TEXTURE_1D
sampler2DShadow 	GL_TEXTURE_2D
samplerCubeShadow 	GL_TEXTURE_CUBE_MAP
sampler2DRectShadow 	GL_TEXTURE_RECTANGLE
sampler1DArrayShadow 	GL_TEXTURE_1D_ARRAY
sampler2DArrayShadow 	GL_TEXTURE_2D_ARRAY
samplerCubeArrayShadow 	GL_TEXTURE_CUBE_MAP_ARRAY

genType exp(genType α)	returns the natural exponential of a, i.e., eα
genType log(genType α)	returns the natural logarithm of α. If the value returned is β then α = eβ
genType exp2(genType α)	returns 2α
genType log2(genType α)	returns the base 2 logarithm of α. If the value returned is β then α = 2β
genType sqrt(genType α)	returns the square root of α i.e., √α. Returned value is undefined if α < 0.
genType inversesqrt(genType α)	returns the inverse of the square root of α i.e., 1/√α. Returned value is undefined if α <= 0.

genType radians(genType d)	converts degrees to radians
genType degrees(genType r)	converts radians to degrees
genType sin(genType r)	trigonometric sine function
genType cos(genType r)	trigonometric cosine function
genType tan(genType r)	trigonometric tangent function
genType asin(genType x)	trigonometric arc sine function. Returns a value between -π/2 to π/2. The returned value is undefined if |x| > 1.
genType acos(genType x)	trigonometric arc cosine function. Returns a value between 0 to π/2. The returned value is undefined if |x| > 1.
genType atan(genType x, genType y)	trigonometric arc tangent function of y/x. Returns a value between -π to π. The returned value is undefined if x and y are both 0.
genType atan(genType yx)	trigonometric arc tangent function of yx. Returns a value between -π/2 to π/2.

genType abs(genType α)	returns the absolute value of α.i.e, -α if α < 0;
genType sign(genType α)	returns

    -1 for α < 0
    0 for α = 0
    1 for α > 0

genType floor(genType α)	returns the nearest integer less than or equal to α
genType ceil(genType α)	returns the nearest integer greater than or equal to α
genType mod(genType α, float β)

genType mod(genType α, genType β) 	equivalent to α%βin Java
genType min(genType α, float β)

genType min(genType α, genType β) 	returns

    α when α < β
    &beta when β < α

genType max(genType α, float β)

genType max(genType α, genType β) 	returns

    α when α > β
    &beta when β > α

genType clamp(genType α, float β, float δ)

genType clamp(genType α, genType β, genType δ) 	returns

    α when β < α < δ
    β when α > β
    δ when α > δ

genType mix(genType α, float β, float δ)

genType mix(genType α, genType β, genType δ) 	returns the linear blend of α and β. i.e. α + δ(β - α)
genType step(float limit, genType α)

genType step(genType limit, genType α) 	returns

    0 when α < limit;
    1 when α > limit;

genType smoothstep(float α0, float α1, genType β)

genType smoothstep(genType α0, genType α1, genType β) 	returns

    0 when β < α0
    1 when β > α1;
    smooth Hermite interpolation
    when α0 < β < α1


    float length(genType α)	returns the length of a vector α
    float distance(genType α genType β)	returns the distance between α and β
    float dot(genType α, genType β)	returns the dot product of α and β
    vec3 cross(genType α, genType β)	returns the cross product of α and β
    genType normalize(genType α)	returns the nomalized vector of α. i.e. α with a length of 1.
    vec4 ftransform()	only accessiable to vertex shader this function transforms the incoming
    vertex just as the OpenGL fixed-functionality transform ( ftransform ).
    This function can be used to assign a value to gl_Position when no vertex
     manipulation is intended for the vertex shader.
    genType normalize(genType α)	returns the nomalized vector of α. i.e. α with a length of 1.
    genType faceforward(genType N, genType I, genType Nref)	If dot(Nref, I) < 0
    return N; otherwise return -N

    void main()
    {
      vec4 firstData = texture(someSampler, textureCoords);

      vec2 otherTexDx = dFdx(otherTexCoords);
      vec2 otherTexDy = dFdy(otherTexCoords);
      vec2 thirdTexDx = dFdx(thirdTexCoords);
      vec2 thirdTexDy = dFdy(thirdTexCoords);

      if (parameterValue < 20)
      {
          firstData += textureGrad(someOtherSampler, otherTexCoords, otherTexDx, otherTexDy);
      }

      vec4 moreData = textureGrad(thirdSampler, thirdTexCoords, thirdTexDx, thirdTexDy);
    }
