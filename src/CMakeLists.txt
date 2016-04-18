cmake_minimum_required(VERSION 3.0)

project(Matrix)
add_compile_options(-std=c++11 -O3 -DVERBOSE=1)
add_executable(_matrix main.cpp Matrix.cpp MatrixTransformations.cpp MatrixLineOperations.cpp MatrixAlgorithms.cpp)
