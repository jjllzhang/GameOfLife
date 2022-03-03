CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

PROJECT(GameOfLife)

SET(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(imageloader imageloader.c)
add_executable(imageloadertester imageloadertester.c)