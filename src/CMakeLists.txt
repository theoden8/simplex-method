cmake_minimum_required(VERSION 3.0)

project(Matrix)
add_compile_options(-std=c++11 -O3 -DVERBOSE=1)

file(GLOB MATRIX_SRCS
	*.cpp
)

add_executable(_matrix ${MATRIX_SRCS})
