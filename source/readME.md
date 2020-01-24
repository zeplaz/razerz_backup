
## SUBFOLDERS::source

### basez folder
files and libraries, both internal and 3rd party. (see readme) used across different moduals/commponets etc
programs

### shaderglsl {currently basez}
some examples and unspifed shaders

### animation
building up a test of riged models... under devlopment no tests thus far

### geometry
base non animated meshes, and the mesh parser

### MCP_cmd
will hold the strucutre of the overal system

### milieu
computer, patical systems, and other atmopsher stuff.

### text_render
two text rendeing methods, overlay(using KTX and a more complex for gui using freetype2)

### phyziz
future physics commoentz...

### gen_tools
will hold level gen tools other setups for procedual system etc

### ttests

#### ship_testz
first tests in opengl, buffers, test of baisc lighting{kinda broken}, shaders and static model loader, obj files.  (current build has an  unstable fragment shader deadly loop!. plus alot of the files nessary where moved to the "basez" folder to test animation as i did not want lots of duplicates.. however you can move then back {into root or add basez/ to the include paths}and should compile fine. through i am modifying them currently one they are more stable will unify....
