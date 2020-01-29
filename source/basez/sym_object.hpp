
#include "gl_lib_z.hpp"

static int nextobj_id =0;
static int num_sym_obj =0;

//when genreated call function to load the dynamic praperters, or via the non base?
///

class enum sym_obj_paramz
{
  FBCSYM_
}
class sym_object {

  protected :

  int obj_ID;
  Sym_Object_Type so_type;
  //bool use_pipe = false;

  public :
  //virtual void initalize()=0;
  //virtual void draw() =0;
  //virtual void update() =0;
  virtual void config(std::vector<>) = 0;

  void set_id(int in_id =0)
  {
    if(in_id = 0)
    {
      obj_ID = nextobj_id;
      nextobj_id++;
    }
    else{
      obj_ID=in_id;
    }
    num_sym_obj++;
  }


  void set_type(Sym_Object_Type in_so_t)
  {
    so_type=in_so_t;
  }

  int get_id()
  {
    return obj_ID;
  }


};
