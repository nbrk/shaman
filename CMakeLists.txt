cmake_minimum_required(VERSION 3.5)

project(shaman LANGUAGES C)
set(CMAKE_C_STANDARD 90)

set(SRCS
  include/shaman.h
  src/shaman.c
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
