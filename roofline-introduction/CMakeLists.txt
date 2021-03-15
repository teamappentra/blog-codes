cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang")

set(CMAKE_CXX_FLAGS "-march=core-avx2 -ffast-math -g -O3 -lstdc++ ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-march=core-avx2 -ffast-math -g -O3  ${CMAKE_C_FLAGS}")

project("roofline-test")

add_executable(roofline-test roofline-test.c)
target_link_libraries(roofline-test m)

