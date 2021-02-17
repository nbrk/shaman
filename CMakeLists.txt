cmake_minimum_required(VERSION 3.5)

project(shaman LANGUAGES C)

set(SRCS
  shaman.h

  include/shaman.h

  src/shaman_internal.h
  src/s_utils.c
  src/s_program.c
  src/s_get.c
  src/s_set.c
  )

add_library(shaman SHARED ${SRCS})
target_include_directories(shaman PRIVATE /usr/local/include)
target_link_directories(shaman PRIVATE /usr/local/lib)
target_link_libraries(shaman PRIVATE GLEW)
target_include_directories(shaman PUBLIC include/)

set_target_properties(shaman PROPERTIES PUBLIC_HEADER include/shaman.h)
install(TARGETS shaman
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


add_subdirectory(test)
