cmake_minimum_required(VERSION 3.26)
project(demo_05)

set(CMAKE_CXX_STANDARD 17)

add_executable(demo_05 main.cpp
        RBTree.h
        AVLTree.h
        BinarySeachTree.h
)
