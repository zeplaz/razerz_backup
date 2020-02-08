#pragma once

#include "parserlib.hpp"
#include "../shader_lib.hpp"

#include <map>
//static std::vector<shader_tuple_type*> shader_tuple_vec;
static std::map<unsigned int,shader_tuple_type*> shader_tuple_map;

shader_tuple_type* return_new_shader_tuple();
std::map<unsigned int,shader_tuple_type*>* return_shdrmap_ptr_TV();
void size_of_tuplevec();
int run_parse();
//std::vector<shader_tuple_type*>* return_ptr_shader_TV();
