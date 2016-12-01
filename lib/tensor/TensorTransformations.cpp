#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(T)
void Tensor<T>::Pop() {
	grid_.pop_back();
}

temptensor(T)
void Tensor<T>::Push(const T value) {
	grid_.push_back(value);
}

temptensor_a(T, A)
void Tensor<T>::Push(const A &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

temptensor(T)
void Tensor<T>::Resize(const size_t new_size, const T value) {
	return Tensor<T>(Size(), [&](const size_t idx) {return grid_[Size() - idx - 1];});
}
