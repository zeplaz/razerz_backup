#pragma once
#include<time.h>
#include<chrono>

#include "../basez/gl_lib_z.hpp"
#include "../basez/shader_pipeline_CMD.hpp"
#include "../basez/lenz.hpp"


/*
REMBER YOU MUST SET THE SHADER PROGRAMS LENZ AND ORGIAN BEFORE CALLING INIT!
ORGIN USES PIXEL SPACE! KINDA>
*/

constexpr int  VERTEX_BINDER = 0;
constexpr int  PARTCL_UNI_BIDN_INDX = 3;
constexpr int  PARTCL_U_VELOC_INDEX =4;
constexpr int  PARTCL_U_POS_INDEX =5;
constexpr int  PARTCL_U_ORGIN_INDEX =6;

constexpr int  MAX_ATTRACTORS = 24;

constexpr int  PARTC_ENV_BUFFZ = 2;

constexpr int  PARTICLE_GROUP_SIZE     = 512;
constexpr int  PARTICLE_GROUP_COUNT   = 4096;
constexpr int  PARTICLE_COUNT          = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT);


static inline  long tick_current_return()
  {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    auto ap_now_epo = now_ms.time_since_epoch();
    long now_duration = ap_now_epo.count();

    std::chrono::milliseconds dur(now_duration);
    std::chrono::time_point<std::chrono::system_clock> dt_tic(dur);
    std::cout << "\n->#LONG TICCK RETURN::"<< now_duration <<'\n';
    return now_duration;
  }

  static inline float random_float()
  {
    float res;
    unsigned int tmp;
    static unsigned int seed = 0xFFFF0C59;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    //std::cout << "\nres::"<<res << " rez-1.0f" << res - 1.0f <<'\n';
    return (res - 1.0f);
   }

  static glm::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
  {
      glm::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
      randomvec = glm::normalize(randomvec);
      randomvec *= (random_float() * (maxmag - minmag) + minmag);

    //  std::cout <<"\nradvec::" << 'x'<< randomvec.x <<'\n'
    //  <<'y' <<randomvec.y << '\n'
    //  <<'z' << randomvec.y << '\n';
      return randomvec;
  }




class comput_partic_sim
{

  union
      {
        struct
          {
              GLuint position_buffer;
              GLuint velocity_buffer;
          };
          GLuint p_buffz[PARTC_ENV_BUFFZ];
      };

      union
  {
      struct
      {
          GLuint position_tbo;
          GLuint velocity_tbo;
      };
      GLuint tbos[2];
  };

  private :
  GLint  dt_location;

  GLuint attractor_buffer;
  float attractor_masses[MAX_ATTRACTORS];

  view_lenz* active_lenz;

  GLuint  render_vao;
  GLuint  render_vbo;

  GLuint comput_prog_ID;
  GLuint render_prog_ID;
  public :

  static long frame_count;
  GLuint last_ticks=0;
  GLuint start_ticks=0;
  GLuint current_time=0;

  float time;
  float delta_time;

  glm::vec4 orgin;
  GLuint orgin_ID;
  GLuint orgin_loc;
  void init();
  void partical_dispaly();
  inline void set_orgin(glm::vec4 in_orgin)
  {
    orgin=in_orgin;
  }

  inline  void set_lenz(view_lenz* in_lenz)
    {
      active_lenz = in_lenz;
    }

  void  set_uniform_loc()
  {
   dt_location = glGetUniformLocation(comput_prog_ID, "dt");
   orgin_loc = glGetUniformLocation(comput_prog_ID, "orgin");
  }

  void set_renderz_ID(gl_shader_t* in_comp_shd,gl_shader_t* in_rend_shd)
  {
    comput_prog_ID =in_comp_shd->program_ID;
    render_prog_ID =in_rend_shd->program_ID;
  }




};
