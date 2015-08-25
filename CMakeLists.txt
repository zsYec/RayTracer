cmake_minimum_required(VERSION 3.2)
project(Ray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Ray ${SOURCE_FILES} Vector3.h Color.h Ray3.h IntersectResult.h Geometry.h BMPWriter.h Scene.h Material.h PerspectiveCamera.h RayTracing.h)