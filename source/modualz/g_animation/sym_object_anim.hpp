
#include "assimp_scene_loader.hpp"
#include "basez/sym_object.hpp"

class sym_object_anim : public sym_object
{
  private :
  bool is_animated;
  skeleton obj_skeleton;
  std::vector<animated_mesh> obj_meshes;
  std::unordered_map<std::string,animation> obj_animations;
  std::unordered_map<std::string,animation>::iterator itr_anim;

  public :

  virtual void update_skeleton();
  void draw_animated(gl_shader_t* shader);

  void add_animation(std::string ani_name, animation& in_anim);
  animated_mesh* find_animation(std::string anim_to_find);

  void play_animation(animation& amin, bool loop=false,bool reset_to_start = false);
  void stop_animating();

  void load_meshes(assimp_scene_loader& loader);

};

sym_object_anim::draw_animated(gl_shader_t* shader)
{
  if(is_animated)
  {
    update_skeleton();
    for(size_t i = 0; i<obj_meshes.size(); i++)
    {
      obj_meshes.at(i).draw_animated(shader);
    }
  }
  else
  {
    obj_meshes.at(i).draw(shader);
  }
}

sym_object_anim::load_meshes(assimp_scene_loader& loader)
{
  obj_meshes = loader.get_meshes();
  if(obj_meshes!=0)
  {
    obj_skeleton =   obj_meshes.at(0).
  }
}

void sym_object_anim::add_animation(std::string ani_name, animation& in_anim)
{

  obj_animations.insert(make_pair(ani_name,in_anim);
}

animation* sym_object_anim::find_animation(std::string anim_to_find)
{
  itr_anim = obj_animations.find(anim_to_find);
  if ( itr_anim == itr_anim.end() )
  {
    std::cout << "joint not found\n";
    return nullptr;
  }
  else
    return &itr_anim->second;
}

sym_object_anim::play_animation(animation& amin, bool loop=false,bool reset_to_start = false)
{
obj_skeleton.play_animation(amin,loop,reset_to_start);
}

void sym_object_anim::stop_animating();
{
  obj_skeleton.stop_animating();
}
