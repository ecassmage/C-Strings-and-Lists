cmake_minimum_required(VERSION 3.17)
project(C_Strings_and_Lists C)

set(CMAKE_C_STANDARD 99)

add_executable(C_Strings_and_Lists tester.c list.h str.h error.h)