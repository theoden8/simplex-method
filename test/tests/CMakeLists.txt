cmake_minimum_required(VERSION 2.6)

include_directories(
	${PROJECT_SRC}
)

add_executable(_matrix main.cpp)
target_link_libraries(_matrix matrix)
