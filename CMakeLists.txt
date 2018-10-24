CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(metaxxa)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/definitions.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/include_directories.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/libraries.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/sources.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/util.cmake)

REQUIRE_CXX_17()

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/cmakemodules/targets.cmake)