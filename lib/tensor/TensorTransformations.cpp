#pragma once

#include "Tensor.hpp"

template <typename T, typename L>
void Tensor<T, L>::Pop() {
	grid_.pop_back();
}

template <typename T, typename L>
void Tensor<T, L>::Push(const T value) {
	grid_.push_back(value);
}

template <typename T, typename L>
template <typename A>
void Tensor<T, L>::Push(const A &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

template <typename T, typename L>
void Tensor<T, L>::Resize(const size_t new_size, const T value) {
	grid_.resize(new_size, value);
}
