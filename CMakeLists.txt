cmake_minimum_required(VERSION 3.22)
project(PenguinCafe)

set(CMAKE_CXX_STANDARD 11)

set(LD_DEBUG all)

find_package(OpenGL REQUIRED)
find_library(GLFW_LOCAL glfw3 lib)

include_directories(include)
include_directories(headers)

set(SOURCE_FILES
        src/glad.c
        src/stb_image.cpp
        src/tiny_obj_loader.cpp
        src/rendering/text.cpp
        src/wrong/matrices.cpp
        src/globals/structs.cpp
        src/globals/variables.cpp
)

add_executable(PenguinCafe main.cpp ${SOURCE_FILES})
target_link_libraries(PenguinCafe OpenGL::GL)
target_link_libraries(PenguinCafe ${GLFW_LOCAL})
