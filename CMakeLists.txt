cmake_minimum_required(VERSION 3.27)
project(CPP_Timer)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Timer main.cpp
        Timer/timer.h
        Timer/timer.cpp)
