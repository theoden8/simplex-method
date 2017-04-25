#include "Tensor.hpp"

template <typename T>
void Tensor<T>::Pop() {
	grid_.pop_back();
}

template <typename T>
void Tensor<T>::Push(const T value) {
	grid_.push_back(value);
}

template <typename T> template <typename A>
void Tensor<T>::Push(const A &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

template <typename T>
void Tensor<T>::Resize(const size_t new_size, const T value) {
	grid_.resize(new_size, value);
}
