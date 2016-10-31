#include "Tensor.hpp"

Tensor<0>::Tensor(tensor_t val):
	grid_(val)
{}

Tensor<0>::~Tensor()
{}

const Tensor<0>::tensor_t &Tensor<0>::GetGrid() {
	return grid_;
}

size_t Tensor<0>::Size() const {
	return 1;
}


Tensor<0>::operator Tensor<0>::tensor_t() {
	return grid_;
}

const Tensor<0>::operator Tensor<0>::tensor_t() const {
	return grid_;
}


void Tensor<0>::operator +=(real_t val) {
	grid_ += val;
}

void Tensor<0>::operator -=(real_t val) {
	grid_ -= val;
}

void Tensor<0>::operator *=(real_t val) {
	grid_ *= val;
}

void Tensor<0>::operator /=(real_t val) {
	grid_ /= val;
}
