cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(hello LANGUAGES CXX)

add_executable(test ${PROJECT_SOURCE_DIR}/test.cpp)