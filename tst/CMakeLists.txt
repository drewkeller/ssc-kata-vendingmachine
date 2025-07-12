add_executable(mytests Setup_test.cpp)
target_link_libraries(mytests PRIVATE gtest gtest_main gmock gmock_main)
include(GoogleTest)
gtest_discover_tests(mytests)