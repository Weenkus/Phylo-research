cmake_minimum_required(VERSION 3.3)
project(SeqClust)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp ClusterAlgorithms/Sequential.cpp ClusterAlgorithms/Sequential.h
        Utils/Help.cpp Utils/Help.h Utils/HashParser.cpp Utils/HashParser.h)

add_executable(SeqClust ${SOURCE_FILES})