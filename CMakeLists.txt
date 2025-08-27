cmake_minimum_required(VERSION 3.10)
project(logic-gate-language)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(src)

# Collect all source files except main.cpp
file(GLOB_RECURSE LIB_SOURCES 
    "src/*.cpp"
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Create library
add_library(logic-gate-lib STATIC ${LIB_SOURCES})

# Create main executable
add_executable(logic-gate-language src/main.cpp)
target_link_libraries(logic-gate-language logic-gate-lib)

# Find gtest
find_package(GTest QUIET)
if(GTest_FOUND)
    # Create test executable
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests logic-gate-lib GTest::gtest GTest::gtest_main)
    include_directories(tests)
endif()