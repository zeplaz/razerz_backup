#include "../basez/sym_object.hpp"



int main(int argc, char* argv[])
{

  sym_object tso;

  tso.set_obj_type(Sym_Object_Type::TEXTURE_OBJ);

  //std::cout  << "objecttype::test::" << tso.so_type;
  std::string sometestlog = "testloglolal\n";
  tso.logger(&tso,sometestlog);
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
