cmake_minimum_required(VERSION 3.15)
project(mc_rpl_sample C ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_library(${PROJECT_NAME} OBJECT
        src/main.c
        src/patcher.c
        src/syscalls.S
        src/util.c
)

target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
)
target_include_directories(${PROJECT_NAME} PUBLIC
        src
)

add_subdirectory(src/cemu)
add_subdirectory(src/aroma)

