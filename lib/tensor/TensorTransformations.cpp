#include "Tensor.hpp"
#include "TensorTemplates.hpp"


template <class T>
void Tensor<T>::Pop() {
	grid_.pop_back();
}

template <class T>
void Tensor<T>::Push(const T value) {
	grid_.push_back(value);
}

template <class T> template <class A>
void Tensor<T>::Push(const A &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

template <class T>
void Tensor<T>::Resize(const size_t new_size, const T value) {
	return Tensor<T>(Size(), [&](const size_t idx) {return grid_[Size() - idx - 1];});
}
