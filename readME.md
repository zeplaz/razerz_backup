
# razerz
testbed of an openGL graphics rendering engine.

many small unit experments and tests, building up to a larger program, you can find, smaller units, 
with their tests, (however reactecturing has resulted in some broken includes)
... nevertheless, progject should slowly move to unify the parts. 
list of contained folders: to find the meat, go to the source folder and check the readme

## Folders

### test_rezultz_et_backupz
images of tests outpus,

## SUBFOLDERS::test_rezultz
#### binary_backupz
example binaries backups as well.
#### oldcode_backupz
reivsion control backup of iterations..

### lib_othr
just bits of files, and examples and notes

### build_stuff 
likely will be moved, scatchspace for autotools. and cmake etc. 

### source
containes the source code for various moduals and programs, and tests in building up engine.

## SUBFOLDERS::source

### basez folder
files and librays and other aspects used across diffrent moduals/commoents
programs

### animation folder
building up a test of riged models... under devlopment no tests thus far

### phyziz folder
future physics commoentz...

### text_render
two text rendeing methods, overlay(using KTX and a more complex for gui using freetype2)

### shaderglsl folder
some examples and unspifed shaders

### Ship_testz folder
first tests in opengl, buffers, test of baisc lighting{kinda broken}, shaders and static model loader, obj files.  (current build has an  unstable fragment shader deadly loop!. plus alot of the files nessary where moved to the "basez" folder to test animation as i did not want lots of duplicates.. however you can move then back {into root or add basez/ to the include paths}and should compile fine. through i am modifying them currently one they are more stable will unify....

#### Current complie line:
(these are not always uptodate check local Readme)

addding makefiles and other autotools soon

##### for ships
g++ -std=c++17  -Wall -Wextra  main_shpr2_test.cpp   shader_parser.cpp  geometry.cpp opengl_utilityz.cpp geometry_parser.cpp  `pkg-config --cflags gldw3 ` -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp

##### for textrender
 g++ -std=c++17  -Wall -Wextra  p_test.cpp text_render.cpp ../basez/3rdparty/sb7ktx.cpp  -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp -I/usr/include/freetype2  -L/usr/local/lib -lfreetype

