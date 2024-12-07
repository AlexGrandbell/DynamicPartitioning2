cmake_minimum_required(VERSION 3.28)
project(DynamicPartitioning2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DynamicPartitioning2
        FirstRAM.h
        main.cpp
        WorstRAM.h
        RAM.h
        RAM.cpp
        CPU.h
        Menu.cpp)
