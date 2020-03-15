
## shipz tests

### data_extrn
has texture and model data for test

#### NOTE!!!
this was the 1st build working with opengl many of the files and aspects have been broken down and moved. it should be still compliable...
with fixing up paths... also shader locations are currently local for this...

##### for ships {outdated}
g++ -std=c++17  -Wall -Wextra  main_shpr2_test.cpp   shader_parser.cpp  geometry.cpp opengl_utilityz.cpp geometry_parser.cpp -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp
