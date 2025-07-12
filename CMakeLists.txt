cmake_minimum_required(VERSION 3.5...4.10)
project(VendingMachine)
enable_testing()
add_subdirectory(lib/googletest) # Adjust path as needed
include_directories(lib/googletest/include) # Adjust path as needed
#add_subdirectory(src)
add_subdirectory(tst)