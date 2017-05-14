#pragma once

#include "Tensor.hpp"

template <typename T, typename L>
T &Tensor<T, L>::operator[] (size_t idx) {
	return grid_[idx];
}

template <typename T, typename L>
const T &Tensor<T, L>::operator[] (size_t idx) const {
	return grid_[idx];
}

template <typename T, typename L>
size_t Tensor<T, L>::Size() const {
	return grid_.size();
}

template <typename T, typename L>
Tensor<T, L>::operator Tensor<T, L>::tensor_t() const {
	return grid_;
}

template <typename T, typename L>
const typename Tensor<T, L>::Tensor::tensor_t &Tensor<T, L>::GetGrid() const {
	return grid_;
}
