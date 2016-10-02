cmake_minimum_required(VERSION 3.3)
project(SeqHash)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++11")

set(SOURCE_FILES main.cpp Utils/FastaParser.cpp Utils/FastaParser.h SimHash.cpp SimHash.h
        HashFunctions/SpookyV2/SpookyV2.cpp HashFunctions/SpookyV2/SpookyV2.h Utils/Help.cpp
        Utils/Help.h Utils/ScoreMatrix.cpp Utils/ScoreMatrix.h HashFunctions/Blash/Blash.cpp
        HashFunctions/Blash/Blash.h Utils/AlphabetReduction.cpp Utils/AlphabetReduction.h)
add_executable(SeqHash ${SOURCE_FILES})

