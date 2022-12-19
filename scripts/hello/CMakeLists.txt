
find_package(OpenGL REQUIRED)

# add a executable file
add_executable(hello hello.cpp)

# add link file
target_link_libraries(hello pmp_vis)


