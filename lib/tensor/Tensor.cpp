#include "Tensor.hpp"
#include "TensorTemplates.hpp"

temptensor(T)
Tensor<T>::Tensor(size_t size):
	grid_(size)
{}

temptensor(T)
Tensor<T>::Tensor(size_t size, T value):
	grid_(size, value)
{}

temptensor(T)
Tensor<T>::Tensor(tensor_t grid):
	grid_(grid)
{}

temptensor(T)
Tensor<T>::~Tensor()
{}
