cmake_minimum_required(VERSION 3.17)
project(OpemGL_Study)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(OpemGL_Study main.cpp)

target_link_libraries(OpemGL_Study opengl32 glew32 glfw3)