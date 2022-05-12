cmake_minimum_required(VERSION 3.22)
project(Ray_Tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ray_Tracing main.cpp include/vec3.h include/color.h include/ray.h include/hittable.h include/sphere.h include/hittable_list.h include/raytracer.h include/camera.h)
