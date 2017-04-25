#include "Tensor.hpp"


template <class T>
T &Tensor<T>::operator[] (size_t idx) {
	return grid_[idx];
}

template <class T>
const T &Tensor<T>::operator[] (size_t idx) const {
	return grid_[idx];
}

template <class T>
size_t Tensor<T>::Size() const {
	return grid_.size();
}

template <class T>
Tensor<T>::operator Tensor<T>::tensor_t() {
	return grid_;
}

template <class T>
const Tensor<T>::Tensor::tensor_t &Tensor<T>::GetGrid() const {
	return grid_;
}
