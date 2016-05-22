cmake_minimum_required(VERSION 3.5)
project(SeqHits)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++11")

set(SOURCE_FILES main.cpp Utils/Help.cpp Utils/Help.h Utils/FastaParser.cpp Utils/FastaParser.h Core/Hits.cpp Core/Hits.h)
add_executable(SeqHits ${SOURCE_FILES})