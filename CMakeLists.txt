cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(BUDDY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-fopenmp -Werror=return-type")

find_package(OpenCV REQUIRED)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

# Find our libraries
list(APPEND LIBRARY_NAMES
  hermes)
  # theia)

add_subdirectory(hermes)
# add_subdirectory(theia)
