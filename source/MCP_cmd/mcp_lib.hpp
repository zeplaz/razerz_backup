
#pragma once
#include "basez/gl_lib_z.hpp"


template<typename Inher_type>
class singleton
{
  protected :
  singleton() = default;

  public :
  singleton(const singleton&) = delete;
  singleton &operator = (const singleton&)=delete;

  static Inher_type &get_instance()
  {
    static Inher_type instance;
    return instance;
  }
};
