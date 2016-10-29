#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(N)
Tensor<N>::Tensor(size_t size):
	grid_(size)
{}

temptensor(N)
Tensor<N>::Tensor(size_t size, Tensor <N - 1> value):
	grid_(size, value)
{}

temptensor(N)
Tensor<N>::Tensor(tensor_t grid):
	grid_(grid)
{}

temptensor(N)
Tensor<N>::~Tensor()
{}
