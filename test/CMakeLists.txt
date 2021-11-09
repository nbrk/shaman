add_executable(test1 test1.c)
target_include_directories(test1 PRIVATE /usr/local/include)
target_link_directories(test1 PRIVATE /usr/local/lib)
target_link_libraries(test1 PRIVATE shaman GLEW GL glfw )


add_executable(test2 test2.c)
target_include_directories(test2 PRIVATE /usr/local/include)
target_link_directories(test2 PRIVATE /usr/local/lib)
target_link_libraries(test2 PRIVATE shaman GLEW GL glfw )
