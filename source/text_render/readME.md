### to compile:

g++ -std=c++17  -Wall -Wextra -g  p_test.cpp text_render.cpp ../basez/3rdparty/sb7ktx.cpp ../basez/opengl_utilityz.cpp -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp -I/usr/include/freetype2  -L/usr/local/lib -lfreetype




#### text_render_gui
utilizes and loads freetype fonts

#### text_overlay
uses ktx and the sb7 loader
note can use toktx to make ktx for the overlayfonter.
