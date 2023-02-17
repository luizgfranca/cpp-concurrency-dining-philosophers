cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

project(dining_philosophers)
add_executable(dining_philosophers 
    main.cpp 
    philosopher.cpp
    fork.cpp
    )