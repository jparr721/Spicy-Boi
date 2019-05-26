cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(hermes LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "-std=c18 ${CMAKE_C_FLAGS}")

find_package(bluez REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include"
  ${BLUEZ_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCE_DIR}/src/main.c
  ${PROJECT_SOURCE_DIR}/src/scanner.c)

target_link_libraries(
  ${PROJECT_NAME}
  ${BLUEZ_LIBRARY_DIRS})
