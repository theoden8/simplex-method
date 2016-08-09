cmake_minimum_required(VERSION 2.8)

project(Tensor)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

file(GLOB TENSOR_SRCS
	*.cpp
)

add_library(tensor STATIC ${TENSOR_SRCS})

# add_library(matrix_so SHARED ${TENSOR_SRCS})
# add_dependencies(matrix_so vector_so)
