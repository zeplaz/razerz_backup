
set(CMAKE_C_COMPILER gcc)
cmake_minimum_required(VERSION 3.6.3 FATAL_ERROR)

project(text_render LANGUAGES CXX)

include(ExternalProject)

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/freetype2")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/..basez/3rdparty/freetype2")

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
include_directories(/usr/include/freetype2)

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
)
set_target_properties(basez PROPERTIES
CMAKE_CXX_STANDARD 17
CMAKE_CXX_EXTENSIONS ON
CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(parserz STATIC
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

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(LIBS glfw3 assimp GLEW freetype 3rdparty basez cmdz gk_objz text_R parserz)

set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELASE)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CXX_FLAGS "-Wall" "-O0" "-Wsuggest-final-types" "-Wsuggest-final-methods"
  "-Wsuggest-final-overrride"  "-Wextra" "-Wpedantic" )
  list(APPEND CXX_FLAGS_DEBUG "-O0" "-Wsuggest-final-types" "-Wsuggest-final-methods"
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
target_compile_options(parserz PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)
target_compile_options(cmdz PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)
target_compile_options(gk_objz PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)
target_compile_options(text_R PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)

target_compile_options(3rdparty PUBLIC
"$<$<CONFIG:DEBUG>:$(CXX_FLAGS_DEBUG)>"
"$<$<CONFIG:RELEASE>:$(CXX_FLAGS_RELEASE)>"
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(text_render p_test.cpp )
target_include_directories(text_render PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(text_render PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

target_link_libraries(text_render ${LIBS} ${OPENGL_LIBRARIES} Threads::Threads OpenGL::GL ${CMAKE_DL_LIBS} ${FREETYPE_LIBRARY} ${GLUT_LIBRARY} ${X11_LIBRARIES})
