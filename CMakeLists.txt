cmake_minimum_required(VERSION 3.14)
project(micrograd.cpp VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compilation targets
## Micrograd library
add_library(
	micrograd
  src/micrograd/micrograd.cpp
)
target_include_directories(
	micrograd
  PUBLIC
	src/micrograd
)

## Main executable TODO: delete when we have python bindings
add_executable(micrograd_exe src/main.cpp)
target_include_directories(micrograd_exe PUBLIC src)
target_link_libraries(micrograd_exe PUBLIC micrograd)

# Testing
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(
	test_mg
  tests/value.cc
)
target_include_directories(
	test_mg
	PUBLIC
	micrograd
)
target_link_libraries(
	test_mg
	GTest::gtest_main
	micrograd
)
include(GoogleTest)
gtest_discover_tests(test_mg)
