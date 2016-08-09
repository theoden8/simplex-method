cmake_minimum_required(VERSION 2.8)

include_directories(
	${TENSOR_LIB}
	${GTEST_LIB}
	${GMOCK_LIB}
)

file(GLOB SRCS
	*.cpp
)

add_executable(_testtensor ${SRCS})
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
target_link_libraries(_testtensor libgtest libgmock)
