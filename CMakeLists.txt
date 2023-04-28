cmake_minimum_required(VERSION 3.23)
project(ex1___Berko_and_Ayal C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex1___Berko_and_Ayal
        IsraeliQueue.h Node.c Node.h main.c main.c)
