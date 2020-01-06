cmake_minimum_required(VERSION 3.15)
project(semaphores C)

set(CMAKE_C_STANDARD 99)

add_executable(semaphores reader-writer-nostarve.c)