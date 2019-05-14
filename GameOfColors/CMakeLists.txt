cmake_minimum_required(VERSION 3.10)
project(GameOfColors)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(GameOfColors
        CMakeLists.txt
        source/main.cpp
        header/Includes.h
        header/Shader.h
        header/VerticesObject.h
        header/Transformations.h
        header/Tilemap.h
        header/ColorTile.h)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_library(Cocoa REQUIRED)
find_library(CoreVideo REQUIRED)
find_library(IOKit REQUIRED)
find_package(GLFW3 REQUIRED)

##/usr/local/lib/libglfw.3.2.dylib

target_link_libraries(GameOfColors /usr/local/lib/libglfw.3.3.dylib ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(GameOfColors PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} /usr/local/include/glm)
