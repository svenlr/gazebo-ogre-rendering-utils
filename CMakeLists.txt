cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

find_package(gazebo REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

## Compile as C++14
add_compile_options(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(render_to_texture SHARED
        src/RenderToTexture.cpp
        )

target_include_directories(render_to_texture SYSTEM PUBLIC ${GAZEBO_INCLUDE_DIRS})
target_include_directories(render_to_texture PRIVATE include)
target_link_libraries(render_to_texture ${GAZEBO_LIBRARIES} -lOgreMain -lOIS)

add_library(png_writer SHARED
        src/png_utils.cpp
        )

target_include_directories(png_writer PRIVATE include)


