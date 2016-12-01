#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(T)
T &Tensor<T>::operator[] (size_t idx) {
	return grid_[idx];
}

temptensor(T)
const T &Tensor<T>::operator[] (size_t idx) const {
	return grid_[idx];
}

temptensor(T)
size_t Tensor<T>::Size() const {
	return grid_.size();
}

temptensor(T)
Tensor<T>::operator Tensor<T>::tensor_t() {
	return grid_;
}

temptensor(T)
const Tensor<T>::Tensor::tensor_t &Tensor<T>::GetGrid() const {
	return grid_;
}
