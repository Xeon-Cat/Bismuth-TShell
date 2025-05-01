cmake_minimum_required(VERSION 3.31)
project(Bismuth C)

set(CMAKE_C_STANDARD 23)
include_directories(include)

add_executable(Bismuth
        include/TermWin.h
        src/TermWin.c
        include/Bismuth.h
        test/main.c
        src/Bismuth.c)
