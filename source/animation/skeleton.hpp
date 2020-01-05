#pragma once

#include "joint.hpp"

#include <map>
#include <unordered_map>


class skeleton
{
  public :
  std::map<std::string,joint> jointz_map;
  std::map<std::string,joint>::iterator iter_joint;

  glm::mat4 global_inverse_matrix;
  std::vector<glm::mat4> joint_matrixz;

  float time;
  float start_time;
  float end_time;

  std::unordered_map<std::string,animation*> animation_map;
  std::unordered_map<std::string,animation*>::iterator itr_anim;


  animation* active_animation;

  bool anim_play;
  bool anim_loop;

  skeleton()
  {
    time = start_time = end_time =0;

    active_animation = nullptr;
    animation* null_animation;
    animation_map.insert(std::make_pair("idel",nullptr));
    anim_loop = false;

  }
  skeleton(std::vector<joint> in_joints, glm::mat4 in_global_inv_tranz)
  {
    init(in_joints,in_global_inv_tranz);

  }

  void init(std::vector<joint> in_joints, glm::mat4 in_global_inv_tranz)
  {

    global_inverse_matrix = in_global_inv_tranz;
    for(size_t i =0; i<in_joints.size(); i++)
    {
      in_joints.at(i).parent_skeleton = this;
      jointz_map.insert(std::make_pair(in_joints.at(i).joint_name,in_joints.at(i)));
    }
    time = start_time = end_time = 0;
    active_animation = nullptr;
    animation_map.insert(std::make_pair("idel",nullptr));
    anim_loop = false;

  }

   joint* find_joint(std::string name)
  {
    iter_joint = jointz_map.find(name);

    if ( iter_joint == jointz_map.end() )
    {
      std::cout << "joint not found\n";
      return nullptr;
    }
    else
      return &iter_joint->second;
  }

  void play_animation(animation& anim, bool loop, bool reset_to_start)
  {
    if(active_animation != nullptr)
    {
      if(anim.priority < active_animation->priority)
      {
        active_animation = &anim;
      }
      else return;
    }
    else
    {
      active_animation = &anim;
    }

    start_time = active_animation->start_time;
    end_time   =  active_animation->end_time;
     anim_play = true;
     anim_loop = loop;

     if(reset_to_start)
     {
       time = active_animation->start_time;
     }
   }

   void stop_animating()
   {
     time=end_time;
     active_animation = nullptr;
     anim_play = false;
   }

  /* void set_idle()
   {
     itr_anim = animation_map.find("idle");

     if ( itr_anim == animation_map.end() )
     {
       std::cout << "idle animation not found\n";
     }
     else
      {
         iter_joint = jointz_map.find("idle");
         if ( iter_joint == animation_map.end() )
         {
           std::cout << "idle joint not found\n";
         }
         else
          itr_anim->second = iter_joint->second;
      }
   }*/

   void set_idle_manual(animation* in_anim)
   {
     itr_anim = animation_map.find("idle");

     if ( itr_anim == animation_map.end() )
     {
       std::cout << "idle not found\n";
     }
     else
        itr_anim->second = in_anim;
   }


  void update_joint_matrixs()
  {
    if(jointz_map.size() == 0)
    {
     return;
    }

    joint_matrixz.clear();
    for(int i =0; i<MAX_JOINTZ; i++)
    {

      if(i>jointz_map.size()-1)
      {
        joint_matrixz.push_back(glm::mat4(1.0));
      }
      else
      {
        i =  jointz_map.size();
        for (std::map<std::string,joint>::iterator it=jointz_map.begin(); it!=jointz_map.end(); ++it)
        {
          joint* temp_joint = &it->second;
          glm::mat4 concat_tranz = (temp_joint->get_parent_transform()* AiToGLMMat4(temp_joint->assimp_node->mTransformation));

          joint_matrixz.push_back(global_inverse_matrix*concat_tranz*temp_joint->offset_matrix);
        }
      }
    }
  }
void update()
{
 update_joint_matrixs();

 if(!anim_play)
 return;

 time += globalz::delta_time*0.001f;

 if(time<start_time)
 {
   time = start_time;
 }

 if(time>end_time)
 {
   if(anim_loop)
   {
     time = start_time;
   }
   else
   {stop_animating();}
 }
 for (iter_joint =jointz_map.begin(); iter_joint != jointz_map.end(); ++iter_joint)
 {
   //joint* temp_joint = &
   iter_joint->second.update_key_fame_transform(time);
   //temp_joint->update_key_fame_transform(time);
 }

}



};
