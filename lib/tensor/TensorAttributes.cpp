#include "Tensor.hpp"
#include "TensorTemplates.hpp"

temptensor(N)
size_t Tensor<N>::Size() const {
	return grid_.size();
}

temptensor(N)
const Tensor<N>::Tensor::tensor_t &Tensor<N>::GetGrid() const {
	return grid_;
}

temptensor(N)
Tensor<N>::operator Tensor<N>::tensor_t() {
	return grid_;
}
