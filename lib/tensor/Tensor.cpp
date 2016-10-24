#include "Tensor.hpp"

#define temptensor(var) template <size_t var>

temptensor(N)
Tensor<N>::Tensor(Tensor<N>::tensor_t grid):
	grid_(grid)
{}

temptensor(N)
Tensor<N>::Tensor(const Tensor<N>::tensor_t &grid):
	grid_(grid)
{}

temptensor(N)
Tensor<N>::~Tensor()
{}

temptensor(N)
size_t Tensor<N>::Size() {
	return grid_.size();
}

temptensor(N)
const Tensor<N>::Tensor::tensor_t &Tensor<N>::GetGrid() {
	return grid_;
}
