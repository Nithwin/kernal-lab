cmake_minimum_required(VERSION 3.20)

project(KernelLab VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(KernelLab
    src/main.cpp
    src/cpu_scheduler/process.cpp
    src/cpu_scheduler/algorithms/fcfs.cpp
    src/cpu_scheduler/utils/schedule_printer.cpp
)