add_executable(test1 test1.c)
target_link_libraries(test1 shaman)


add_executable(test2 test2.c)
target_include_directories(test2 PRIVATE /usr/local/include)
target_link_directories(test2 PRIVATE /usr/local/lib)
target_link_libraries(test2 PRIVATE shaman glut GLEW GL GLU glfw m cglm)
