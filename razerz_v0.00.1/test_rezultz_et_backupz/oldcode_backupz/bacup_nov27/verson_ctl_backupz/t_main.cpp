
#include "mathII.hpp"
#include "mathz.hpp"
#include "colour.cpp"
int main(int argc, char* argv[])
{
mathz::vector3_vala<float> test_v3;
mathz::vector3_vala<float> normz_testV3;
mathz::vector3_vala<float> R_normz_testV3;
mathz::vector3_vala<float> test2_V3;

mathz::vector3_vala<float> cross1_v3;
mathz::vector3_vala<float> cross2_v3;

mathz::vector3_vala<float> sub_v3;
mathz::vector3_vala<float> add_testv3;
float a1[] = {2.4f, 2.4f, 4.3f};
float a2[] = {4.8,5.5,6.7};
std::valarray<float> va1 (a1,3);
std::valarray<float> va2(a2,3);
std::valarray<float> va3=va1-va2;
std::cout <<"testvalsubtrator::" << va3[0] << va3[1]<< va3[2] << '\n';

test_v3[0] = 3.3;
test_v3[1] = 5.4;
test_v3[2] = 7.9;

test2_V3[0] = 5.5;
test2_V3[1] = 3.6;
test2_V3[2] = 17.4;

float x =test_v3[0];
  //std::cout << test_v3;
normz_testV3 = test_v3.New_normalize();

//R_normz_testV3 =  test_v3.R_normalize();
auto dot_n = normz_testV3.dot(test_v3);
auto dot_org = test_v3.dot(normz_testV3);
auto angle1 = test_v3.angle(test2_V3);
std::cout << test_v3 << "::" << normz_testV3 << '\n'
          << "dotz::" << dot_n <<"::"<<dot_org << '\n'
          << "anglez::" <<angle1 << '\n'<<'\n';

cross1_v3 = test_v3.cross(normz_testV3);
cross2_v3 = test_v3.cross(test2_V3);
std::cout << cross1_v3 << test_v3;
std::cout << "presuptacot::" << test2_V3 << test_v3 <<'\n';
sub_v3 = (test2_V3 - test_v3);
std::cout << "postsub::" << test2_V3 << test_v3 <<'\n';

test_v3-=test_v3;
add_testv3 = cross1_v3 + test_v3;
std::cout <<"addtion::" <<  add_testv3 <<'\n';
std::cout <<"subtraction::" << sub_v3 <<'\n';
std::cout <<"subtraction::" << test_v3 <<'\n';
//std::cin >> test2_v3;

return 0;
}
