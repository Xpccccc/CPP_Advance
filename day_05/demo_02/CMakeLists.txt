cmake_minimum_required(VERSION 3.26)
project(demo_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(demo_02 main.cpp
        MyUnordered_Set.h
        MyUnordered_Map.h
        HashTable_Bucket.h)
