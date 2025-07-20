set(TEST_PROJECT ${CMAKE_PROJECT_NAME}_Test)
set(PROJECT_LIB ${CMAKE_PROJECT_NAME}_lib)

set(SOURCES 
    VendingMachineTest.cpp
    )

enable_testing()
add_executable(${TEST_PROJECT} ${SOURCES})
#add_test(NAME ${TEST_PROJECT} COMMAND ${TEST_PROJECT})

target_link_libraries(${TEST_PROJECT} PRIVATE gtest gtest_main gmock gmock_main ${PROJECT_LIB})

include(CTest)
include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT})