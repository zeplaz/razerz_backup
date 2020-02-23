#pragma once
#include "basez/gl_lib_z.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


const float  fram_per_sec =0.041666666667;
static  float time_to_frame(float time)
{
  return time/fram_per_sec;
}

static glm::vec2 frame_to_time(glm::vec2 frames)
{
  return frames*fram_per_sec;
}

class animation
{
public :
std::string name;
float end_time;
float start_time;
int priority;

animation()
{
  start_time = end_time = priority = 0;
}
animation(std::string in_name,glm::vec2 times, int in_priority)
{
  name = in_name;
  start_time = times.x;
  end_time   = times.y;
  priority   = in_priority;

}


};
