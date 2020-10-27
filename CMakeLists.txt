cmake_minimum_required(VERSION 3.5)

project(HeterogeneousTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HeterogeneousTree main.cpp Node.cpp Node.h Tree.cpp Tree.h OperationsWithAny.h)
