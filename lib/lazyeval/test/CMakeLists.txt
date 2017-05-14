cmake_minimum_required(VERSION 2.8)

include_directories(
	#${MATRIX_LIB}
	#${VECTOR_LIB}
	${LAZYEVAL_LIB}
	${GTEST_LIB}
	${GMOCK_LIB}
)

file(GLOB SRCS
	main.cpp
	LZEvalTest.cpp
)

add_executable(_testlzeval ${SRCS})
set(CMAKE_CXX_FLAGS "-std=c++1y -O3")
target_link_libraries(_testlzeval libgtest libgmock)
