cmake_minimum_required(VERSION 3.25)
project(alienproj)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(alienproj main.cpp ufo.cpp heap.cpp RedBlackTree.h hashtable.h)