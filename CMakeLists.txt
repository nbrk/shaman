cmake_minimum_required(VERSION 3.5)

project(shaman LANGUAGES C)

set(SRCS
  include/shaman.h
  src/shaman_internal.h
  src/read.c
  src/textops.c
  src/compile.c
  )

add_library(shaman SHARED ${SRCS})
target_include_directories(shaman PRIVATE /usr/local/include)
target_link_directories(shaman PRIVATE /usr/local/lib)
target_link_libraries(shaman PRIVATE GL GLEW)
target_include_directories(shaman PUBLIC include/)

add_subdirectory(test)
