add_library(basez "")

target_sources(basez
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/opengl_utilityz.cpp

  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/gl_lib_z.hpp
  ${CMAKE_CURRENT_LIST_DIR}/mathII.hpp
  ${CMAKE_CURRENT_LIST_DIR}/mathz.hpp
  ${CMAKE_CURRENT_LIST_DIR}/opengl_utilityz.hpp
)

set_target_properties(basez PROPERTIES
CMAKE_CXX_STANDARD 17
CMAKE_CXX_EXTENSIONS ON
CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(gk_objz "")

target_sources(gk_objz
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/texture.cpp

  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/texture.hpp
  ${CMAKE_CURRENT_LIST_DIR}/lenz.hpp
)

add_library(parserz "")
target_sources(parserz
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/shader_parser.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/shader_parser.hpp
)

add_library(cmdz STATIC
"../basez/shader_pipeline_CMD.hpp"
"../basez/shader_pipeline_CMD.cpp"
)
