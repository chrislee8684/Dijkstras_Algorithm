cmake_minimum_required(VERSION 3.20)
project(Dijstra_s_Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(Dijkstra_s_Algorithm main.cpp hash.cpp heap.cpp hash.h heap.h dijkstra.h dijkstra.cpp)
