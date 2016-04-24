cmake_minimum_required(VERSION 2.8)

include_directories(
	${PROJECT_SRC}
	${GTEST_LIB}
	${GMOCK_LIB}
)

file(GLOB SRCS
	./*.cpp
	${PROJECT_SRC}/Matrix.cpp
	${PROJECT_SRC}/MatrixAlgorithms.cpp
	${PROJECT_SRC}/MatrixLineOperations.cpp
	${PROJECT_SRC}/MatrixTransformations.cpp
	${PROJECT_SRC}/MatrixProperties.cpp
	${PROJECT_SRC}/SimplexMethod.cpp
)
add_executable(_testmatrix ${SRCS})
set(CMAKE_CXX_FLAGS "-std=c++11")
install(TARGETS _testmatrix DESTINATION ${PROJECT_TEST}/bin)
target_link_libraries(_testmatrix libgtest libgmock)
