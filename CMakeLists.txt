cmake_minimum_required(VERSION 3.5...4.10)
set(CMAKE_CXX_STANDARD 20)

project(VendingMachine)
set(PROJECT ${CMAKE_PROJECT_NAME})
set(PROJECT_LIB ${PROJECT}_lib)

add_executable(${PROJECT})
include_directories(src)
add_subdirectory(src)

enable_testing()
add_subdirectory(lib/googletest)
add_subdirectory(tst)
