cmake_minimum_required(VERSION 3.22)
project(hash_table)

set(CMAKE_VERBOSE_MAKEFILE ON)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -g" CACHE STRING "Set C++ Compiler Flags" FORCE)

# include_directories(.)

add_executable(hash_table
                    hash_table.cc
                    hash_table_test.cc
                    main.cc
)

# message ("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
# message ("HEADER_FILES : ${HEADER_FILES}")

