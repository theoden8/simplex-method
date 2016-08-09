#include "Tensor.hpp"

template <size_t DIM>
Tensor<DIM>::Tensor(const Tensor<DIM>::tensor_t &grid):
	grid(grid)
{}
