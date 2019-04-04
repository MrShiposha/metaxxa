cmake_minimum_required(VERSION 3.9)
project(metaxxa-tests)

include_directories(
    ../include
    ../lib
)

file(GLOB TEST_SRC
    "*.h"
    "*.cpp"

    "algorithm/*.h"
    "algorithm/*.cpp"
)

add_executable(metaxxa-tests ${TEST_SRC})