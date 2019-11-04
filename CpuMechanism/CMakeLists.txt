cmake_minimum_required(VERSION 3.14)
project(CpuMechanism C)

set(CMAKE_C_STANDARD 99)

add_executable(CpuMechanism contextSwitchMeasureEins.c)