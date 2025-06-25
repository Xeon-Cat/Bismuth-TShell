cmake_minimum_required(VERSION 3.31)
project(Bismuth C)

set(CMAKE_C_STANDARD 23)
include_directories(include)

add_executable(Bismuth
        include/TermWin.h
        src/TermWin.c

        include/BWinManager.h
        src/BWinManager.c

        example/main.c

        include/Module.h
        src/Module.c

        src/logger/logger.c
        include/logger/logger.h
        )
