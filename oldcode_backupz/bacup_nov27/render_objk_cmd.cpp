#pragma once
#include "render_objk_cmd.hpp"

auto get_buf_oset = [](f_sp_tuple& fetu_tup)
{
  return std::get<GET_FET_NUMVERX>(fetu_tup);
};
