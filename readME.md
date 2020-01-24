
# razerz
testbed of an openGL graphics rendering engine.

many small unit experiments and tests, building up to a larger program, you can find, smaller units, with their tests, (however restructuring has resulted in some broken includes)
... nevertheless, projects should slowly move to unify the parts.
 to find the meat, go to the source folder and check the readmes.

##dependence

REQUIRED:
c++17
openGL 450.

//external libs
-pthread
GLFW
glm
glew
glut
freeglut/?

//loaders
sp7 ktx loader
-SDL2_image
-assimp

//text freetype2
FT_FREETYPE_H
ft2build.h

see linker list on compile instructions per unit(update is often in local readme)

## Folders

### test_rezultz_et_backupz
images of tests outpus, some binarybackups and other  old code.

### lib_othr
just bits of files, and examples and notes build tools examples

### source
contains the source code for the pars,.. in them various modules, programs, and tests in building up engine.

#### Current complie line:
(these are not always update check local Readme)

##### strongly recommend  you USE GNU G++ version 9.2.1
{clang should work with the makefiles.. see makefiles.note}

#### MAKEFILE/CMAKE NOTES.
cmake files are slowly being added to unit tests. check local folder.
note the cmakes currently are rather linux based, and tailored for current setup.
thus, you may need to pass, dependency paths particularity if using the text_render er.
freetype gives some issues. for windows, idk. mabye? play around.
