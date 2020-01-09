
set(CMAKE_C_COMPILER gcc)
cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)

project(text_render LANGUAGES CXX)

include(ExternalProject)
set(ENV{FREETYPE_DIR} "/usr/include/freetype2")
#set(ENV{FREETYPE_DIR} "/usr/local/lib")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/freetype2")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/..basez/3rdparty/freetype2")

#ExternalProject_Get_Property(freetype2a install_dir)
#set(freetype2a_install_dir install_dir)

#include_directories(
#  ${CMAKE_INSTALL_PREFIX}/include/freetype2
#  )
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OpenGL_GL_PREFERENCE GLVND CACHE STRING "Linux-only: if GLVND, use the vendor-neutral GL libraries (default). If LEGACY, use the legacy ones (might be necessary to have optirun/primusrun work)")
set_property(CACHE OpenGL_GL_PREFERENCE PROPERTY STRINGS GLVND LEGACY)
# OpenGL
find_package(OpenGL REQUIRED)
# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLUT REQUIRED)
find_package(X11 REQUIRED)
#find_package(XI REQUIRED)
#find_package(XRANDR REQUIRED)
# GLFW
find_package(GLFW REQUIRED)
message(STATUS "Found GLFW in ${GLFW_INCLUDE_DIR}")

# ASSIMP
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLM_INCLUDE_DIR}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Freetype REQUIRED)
#target_link_libraries(text_render PRIVATE ${FREETYPE_LIBRARIES})
#target_include_directories(text_render PRIVATE ${FREETYPE_INCLUDE_DIRS})

#REETYPE_INCLUDE_DIR_ft2build
#FREETYPE_INCLUDE_DIR_freetype2
#FREETYPE_INCLUDE_DIRS
include_directories(/usr/include/freetype2)
#link_directories(/usr/local/lib)
#link_directories(/usr/local/lib/x86_64-linux-gnu)

#set(FREETYPE_INCLUDE_DIRS /usr/include/freetype2)
#et(FREETYPE_LIBRARY /usr/local/lib/x86_64-linux-gnu/libfreetype.a)

# STB_IMAGE
#add_library(STB_IMAGE )

add_library(3rdparty STATIC
  "../basez/3rdparty/sb7ktx.h"
  "../basez/3rdparty/sb7ktx.cpp"
  "../basez/3rdparty/stb_image.h"

)

add_library(basez STATIC
"../basez/gl_lib_z.hpp"
"../basez/mathII.hpp"
"../basez/mathz.hpp"
"../basez/opengl_utilityz.hpp"
"../basez/opengl_utilityz.cpp"
"../basez/shader_parser.hpp"
"../basez/shader_parser.cpp"
)

add_library(cmdz STATIC
"../basez/shader_pipeline_CMD.hpp"
"../basez/shader_pipeline_CMD.cpp"
)

add_library(gk_objz STATIC
"../basez/texture.hpp"
"../basez/texture.cpp"
"../basez/lenz.hpp"
)

add_library(text_R STATIC
"text_render.hpp"
"text_render.cpp"
)

target_include_directories(basez PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../basez>"
)

target_include_directories(cmdz PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../basez>"
)
target_include_directories(gk_objz PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../basez>"
)

target_include_directories(3rdparty PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../basez/3rdparty>"
)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(LIBS glfw3 assimp GLEW freetype 3rdparty basez cmdz gk_objz text_R)

set_target_properties(basez PROPERTIES
CMAKE_CXX_STANDARD 17
CMAKE_CXX_EXTENSIONS ON
CMAKE_CXX_STANDARD_REQUIRED YES)

set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELASE)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CXX_FLAGS "-Wall")
  list(APPEND CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods"
  "-Wsuggest-final-overrride"  "-Wextra" "-Wpedantic" )
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES clang)
  list(APPEND CXX_FLAGS "-fcolor-diagnostics")
  list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CXX_FLAGS_RELEASE  "-O3" "-Wno-unused")
endif()

target_compile_options(basez PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)


add_executable(text_render p_test.cpp )
target_include_directories(text_render PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(text_render PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

target_link_libraries(text_render ${LIBS} ${OPENGL_LIBRARIES} Threads::Threads OpenGL::GL ${CMAKE_DL_LIBS} ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${X11_LIBRARIES})
