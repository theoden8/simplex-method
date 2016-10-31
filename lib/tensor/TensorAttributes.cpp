#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(N)
Tensor <N - 1> &Tensor<N>::operator[] (size_t idx) {
	return grid_[idx];
}

temptensor(N)
const Tensor <N - 1> &Tensor<N>::operator[] (size_t idx) const {
	return grid_[idx];
}

temptensor(N)
size_t Tensor<N>::Size() const {
	return grid_.size();
}

temptensor(N)
Tensor<N>::operator Tensor<N>::tensor_t() {
	return grid_;
}

temptensor(N)
const Tensor<N>::Tensor::tensor_t &Tensor<N>::GetGrid() const {
	return grid_;
}
