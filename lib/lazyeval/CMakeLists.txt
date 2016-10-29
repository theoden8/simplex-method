cmake_minimum_required(VERSION 2.8)

project(LazyEval)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

file(GLOB LAZYEVAL_SRCS
	*.cpp
)

add_library(lazyeval STATIC ${LAZYEVAL_SRCS})

# add_library(matrix_so SHARED ${MATRIX_SRCS})
# add_dependencies(matrix_so vector_so)
