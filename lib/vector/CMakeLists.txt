cmake_minimum_required(VERSION 2.8)

project(vector)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -DVERBOSE=1")

include_directories(
	${TENSOR_LIB}
)

file(GLOB VECTOR_SRCS
	*.cpp
)

add_library(vector STATIC ${VECTOR_SRCS})
add_dependencies(vector tensor)

#add_library(vector_so SHARED ${VECTOR_SRCS})
