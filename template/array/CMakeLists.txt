cmake_minimum_required(VERSION 3.22)
project(MyVectorLearn)

set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -g" CACHE STRING "Set C++ Compiler Flags" FORCE)

add_executable(myvector
    myvector.cc
    myvector_test.cc
    main.cc
)
