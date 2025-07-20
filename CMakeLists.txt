cmake_minimum_required(VERSION 3.5...4.10)

project(VendingMachine)
set(PROJECT ${CMAKE_PROJECT_NAME})
set(PROJECT_LIB ${PROJECT}_lib)

set(SOURCES
    src/main.cpp
    src/VendingMachine.cpp
    src/VendingMachine.h
    )

#add_subdirectory(src)
#target_sources(VendingMachine PRIVATE src/VendingMachine.cpp)
include_directories(src)

add_executable(${PROJECT}_exe ${SOURCES})
add_library(${PROJECT_LIB} STATIC ${SOURCES})

enable_testing()
add_subdirectory(lib/googletest)
add_subdirectory(tst)




