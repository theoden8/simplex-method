cmake_minimum_required(VERSION 2.8)

project(Matrix)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -DVERBOSE=1")

file(GLOB MATRIX_SRCS
	*.cpp
)

add_library(matrix STATIC ${MATRIX_SRCS})
