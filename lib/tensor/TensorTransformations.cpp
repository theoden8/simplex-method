#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(N)
void Tensor<N>::Pop() {
	grid_.pop_back();
}

temptensor(N)
void Tensor<N>::Push(const subtensor_t value) {
	grid_.push_back(value);
}

temptensor(N)
void Tensor<N>::Push(const Tensor <N> &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

temptensor(N)
void Tensor<N>::Resize(const size_t new_size, const subtensor_t value) {
	return Tensor<N>(Size(), [&](const size_t idx) {return grid_[Size() - idx - 1];});
}
