cmake_minimum_required(VERSION 3.10)
project(cpp_tools)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(test_estop src/test_estop.cpp)

add_executable(test_thread_runner src/test_thread_runner.cpp)