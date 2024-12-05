cmake_minimum_required(VERSION 3.28)
project(DynamicPartitioning2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DynamicPartitioning2
        Process.cpp
        Process.h
        FirstRAM.h
        FirstRAM.cpp
        main.cpp
        BestRAM.cpp
        WorstRAM.h
        WorstRAM.cpp)
