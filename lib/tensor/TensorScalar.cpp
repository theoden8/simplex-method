#include "Tensor.hpp"

#define tempscalar template <>

tempscalar
Tensor<0>::Tensor(tensor_t val):
	grid_(val)
{}

tempscalar
Tensor<0>::~Tensor()
{}

tempscalar
const Tensor<0>::tensor_t &Tensor<0>::GetGrid() {
	return grid_;
}

tempscalar
size_t Tensor<0>::Size() const {
	return 1;
/


tempscalar
Tensor<0>::operator Tensor<0>::tensor_t() {
	return grid_;
}

tempscalar
const Tensor<0>::operator Tensor<0>::tensor_t() const {
	return grid_;
}


tempscalar
void Tensor<0>::operator +=(real_t val) {
	grid_ += val;
}

tempscalar
void Tensor<0>::operator -=(real_t val) {
	grid_ -= val;
}

tempscalar
void Tensor<0>::operator *=(real_t val) {
	grid_ *= val;
}

tempscalar
void Tensor<0>::operator /=(real_t val) {
	grid_ /= val;
}
