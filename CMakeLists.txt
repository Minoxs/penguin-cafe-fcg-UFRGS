cmake_minimum_required(VERSION 3.20)
project(PenguinCafe)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_library(GLFW_STATIC glfw3 lib)
find_library(GLFW_DYNAMIC glfw3dll lib)

include_directories(lib/include)
include_directories(src/headers)

set(SOURCE_FILES
    lib/imp/glad.c
    lib/imp/stb_image.cpp
    lib/imp/tiny_obj_loader.cpp
    lib/imp/matrices.cpp
    src/imp/global/struct.cpp
    src/imp/global/variable.cpp
    src/imp/loading/object.cpp
    src/imp/player/input.cpp
    src/imp/rendering/object.cpp
    src/imp/rendering/shader.cpp
    src/imp/rendering/text.cpp
    src/imp/rendering/window.cpp
    src/imp/rendering/camera.cpp
    src/imp/player/movement.cpp
)

# Executable with static libraries
add_executable(PenguinCafe src/main.cpp ${SOURCE_FILES})
target_link_libraries(PenguinCafe OpenGL::GL)
target_link_libraries(PenguinCafe ${GLFW_STATIC})
#

# Executable with dynamic library
add_executable(PenguinCafeDLL src/main.cpp ${SOURCE_FILES})
target_link_libraries(PenguinCafeDLL OpenGL::GL)
target_link_libraries(PenguinCafeDLL ${GLFW_DYNAMIC})
target_compile_definitions(PenguinCafeDLL PRIVATE GLFW_DLL)
#
