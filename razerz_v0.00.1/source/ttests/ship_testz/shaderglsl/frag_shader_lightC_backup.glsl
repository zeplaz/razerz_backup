#version 450 core

struct Phong_reflection
{
  //ambient light
  vec4 ambient;
  vec4 spot_cone_drection;

//directiona light
  float drectional_srength;

//Point light
float const_attenuation;
float quadr_attenuation;
float linear_attenuation;

//spot light

  float spot_cos_cutoff;
  float spot_exponent;

  //
  float gamma_c;
};

struct light_propertyz
{
  vec4 intensity;
  vec4 position;

  bool is_enabled;
  Phong_reflection phong_light;
  int  Light_type;
};



const int MAX_Lightz = 5;

out vec4 Frag_colour;

in VERTEX_SHADR_OUT
{
   vec2 frag_uv;
   vec3 frag_normal;
   vec4 frag_pos;
   vec3 vertx_lenz_VM;

   vec3 frag_pos_TBN;
   vec3 frag_view_TBN;
   mat3 frag_TBN_matrix;
} in_frag;

layout(std140,binding=2) uniform Meterialz
{
  vec3 emission;
  vec3 ambient_reflect;
  vec3 diffuse_reflect;
  vec3 specular_reflect;
  float shininess;
  bool is_normalmap;
  float alpha;
}meterial;
//uniform Meterialz meterial;

uniform sampler2D active_texture_sampler;
uniform sampler2D normal_mapSampler;

//uniform light_propertyz lightz[MAX_Lightz];

layout (binding = 1,std430) buffer light_blockz
{
  light_propertyz lightzblock[MAX_Lightz];
};


vec3 calculate_specular(vec3 vk_normz,vec4 vk_pos,light_propertyz light ,Meterialz material)
{
  vec3 light_to_loc   = normalize(vk_pos.xyz-light.position);
  vec3 reflect_drect  = normalize(reflect(light_to_loc,normalize(vk_normz)));
  vec3 pos_toview_dirc= normalize(in_frag.vertx_lenz_VM-vk_pos.xyz);
  float spek_angle    = max(0.0,dot(pos_toview_dirc,reflect_drect));
  vec3 spk_final      = material.specular_reflect*pow(spek_angle,material.shininess);
  return spk_final;
}

vec3 drectiona_ligt()
{

}

void main()
{

  //vec3 ambient= vec3(0.13);
  vec3 scatterd = vec3(0.0);
  vec3 spektral_reflect = vec3(0.0);
  vec3 ambient= vec3(0.0);

vec3 active_normal;
  if(meterial.is_normalmap)
  {
    active_normal = texture(normal_mapSampler,in_frag.frag_uv).rgb;
    active_normal= normalize(active_normal*2.0-1.0);

  }
  else {
  active_normal =  in_frag.frag_normal;
  }

for(int i =0; i<MAX_Lightz;i++)
{
  if(!lightzblock[i].is_enabled)
    continue;


    switch(lightzblock[i].Light_type)
    {
      case 0 :
      {
        break;
      }
      //ambient light
      case 1 :
      {
        ambient =lightzblock[i].phong_light.ambient.rgb*meterial.ambient_reflect;
      }
      //diffuse
      case 2 :
      {
        vec3  surface_to_light = normalize(lightzblock[i].position.xyz-in_frag.frag_pos.xyz);
        float diffuseCoefficient =max(0.0,dot(active_normal,surface_to_light));

        scatterd += diffuseCoefficient*lightzblock[i].intensity.rgb*meterial.diffuse_reflect;

        break;
      }

      //speckular
      case 3 :
      {
         vec3 spek_cal  = calculate_specular(active_normal,in_frag.frag_pos,lightzblock[i],meterial);
         spektral_reflect +=spek_cal*lightzblock[i].intensity;
        break;
      }

      //drectional
      case 4 :
      {
        vec3 spek_cal=vec3(0.0);
        vec3 defuz   =vec3(0.0);
        vec3  surface_to_light = normalize(lightzblock[i].position.xyz-in_frag.frag_pos.xyz);
        float diffuseCoefficient =max(0.0,dot(active_normal,surface_to_light));

        if(diffuseCoefficient !=0)
        {
          defuz       =  diffuseCoefficient*lightzblock[i].intensity;
          scatterd   +=  defuz*meterial.diffuse_reflect;

          spek_cal =calculate_specular(active_normal,in_frag.frag_pos,lightzblock[i],meterial);
          spektral_reflect += lightzblock[i].phong_light.drectional_srength*spek_cal*lightzblock[i].intensity.rgb;
         }
        break;
      }
        //pointlight
      case 5 :
        {
          vec3 light_drection = lightzblock[i].position.xyz- in_frag.frag_pos.xyz;
          float light_distance = length(light_drection);
          light_drection = light_drection/light_distance;


          float total_attenuation = 1.0/(lightzblock[i].phong_light.const_attenuation+
                                         lightzblock[i].phong_light.linear_attenuation*light_distance+
                                         lightzblock[i].phong_light.quadr_attenuation*light_distance*light_distance);
         vec3 half_vec    = normalize(light_drection+in_frag.vertx_lenz_VM);

         float diffz = max(0.0,dot(active_normal,light_drection));

         float skplr;
         if(diffz !=0.0)
         {
           float skplr = max(0.0,dot(active_normal,half_vec));
           skplr = pow(skplr,meterial.shininess)*lightzblock[i].phong_light.drectional_srength;

           spektral_reflect += meterial.specular_reflect*skplr*lightzblock[i].intensity*total_attenuation;
           scatterd         += meterial.diffuse_reflect*diffz*lightzblock[i].intensity*total_attenuation;
         }

        break;
        }


        //spot
      case 6 :
      {
        vec3 light_drection = lightzblock[i].position.xyz;
        light_drection = light_drection- in_frag.frag_pos.xyz;
        float light_distance = length(light_drection);
        light_drection = light_drection/light_distance;

        float followspot_cos = dot(light_drection,-lightzblock[i].phong_light.spot_cone_drection);
        float total_attenuation;
        if(followspot_cos<lightzblock[i].phong_light.spot_cos_cutoff)
        {
          total_attenuation = 0.0;
        }
        else
        {
           total_attenuation = 1.0/(lightzblock[i].phong_light.const_attenuation+
                                      lightzblock[i].phong_light.linear_attenuation*light_distance+
                                      lightzblock[i].phong_light.quadr_attenuation*light_distance*light_distance);

          total_attenuation *=pow(followspot_cos,lightzblock[i].phong_light.spot_exponent);
          float defuziz = max(0.0,dot(active_normal,light_drection));

          if(defuziz!=0)
          {
            vec3 skklr = calculate_specular(active_normal,in_frag.frag_pos,lightzblock[i],meterial)*
                         lightzblock[i].phong_light.drectional_srength;


            spektral_reflect += skklr*lightzblock[i].intensity.rgb*total_attenuation;
            scatterd         += meterial.diffuse_reflect*defuziz*lightzblock[i].intensity.rgb*total_attenuation;
          }
        }

        break;
      }
    }//endlightswitch
  }//end lightloop
  vec4  texture_colour = texture(active_texture_sampler, in_frag.frag_uv);
  //vec3 result = min((texture_colour.rgb*scatterd)+spektral_reflect,vec3(1.0f));
  vec3 result = min((texture_colour.rgb*scatterd)+spektral_reflect,vec3(1.0f));
  Frag_colour = vec4(result,meterial.alpha);
}
