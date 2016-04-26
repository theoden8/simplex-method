cmake_minimum_required(VERSION 2.6)

include_directories(
	${PROJECT_SRC}
	${VECTOR_LIB}
	${MATRIX_LIB}
)

add_executable(_simplex simplex.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
target_link_libraries(_simplex matrix vector)
