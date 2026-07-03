cmake_minimum_required(VERSION 3.15)
project(ProyectoMLQ CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilitar advertencias de compilación para asegurar calidad de código senior
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(ProyectoMLQ
        main.cpp
        Process.h Process.cpp
        Queue.h Queue.cpp
        Scheduler.h Scheduler.cpp
        FileManager.h FileManager.cpp
        Process.h
        Process.cpp
        Queue.h
        Queue.cpp
        Scheduler.h
        Scheduler.cpp
        FileManager.h
        FileManager.cpp
)