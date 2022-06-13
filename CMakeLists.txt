cmake_minimum_required(VERSION 3.22)
project(untitled C)

include_directories(includes/ linenoise/)

set(CMAKE_C_STANDARD 99)

add_executable(
        ftdbg
        srcs/main.c
)
