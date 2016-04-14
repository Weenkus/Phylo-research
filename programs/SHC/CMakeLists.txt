cmake_minimum_required(VERSION 3.3)
project(SHC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp Utils/FastaParser.cpp Utils/FastaParser.h SimHash.cpp SimHash.h HashFunctions/SpookyV2/SpookyV2.cpp HashFunctions/SpookyV2/SpookyV2.h)
add_executable(SHC ${SOURCE_FILES})

