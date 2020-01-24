
#include "mcp_lib.hpp"

typedef GLfloat Vport_array[4];




class viewport {

private :

std::unorderd_map<int,std::vector<int>> render_obj_map;



public :
void set_viewport(GLuint index, Vport_array in_array)
{
  glViewportIndexedfv(index,in_array);
}

void set_VP_depth_range(GLuint index, GLdouble n, gldouble f)
{
  glDeptheRangeIndexed(index,n,f);
}

};
