find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Test for read_mat
add_executable(test_readmat file/test_readmat.cpp)
target_link_libraries(test_readmat
    GTest::gtest
    GTest::gtest_main
    cnpy
    Threads::Threads
)
target_include_directories(test_readmat PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(test_readmat)