#include "Tensor.hpp"
#include "TensorTemplates.hpp"



temptensor_tr(T, R)
R Tensor<T>::operator+() const {
	return *this;
}

temptensor_tr(T, R)
R Tensor<T>::operator-() const {
	Tensor <T> other(*this);
	for(auto &it : other.grid_)
		it = -it;
	return other;
}



temptensor_trs(T, R, S)
R Tensor<T>::operator+(const S scalar) const {
	R other(*this);
	other += scalar;
	return other;
}

temptensor_trs(T, R, S)
R Tensor<T>::operator-(const S scalar) const {
	operator+(-scalar);
}

temptensor_trs(T, R, S)
R Tensor<T>::operator*(const S scalar) const {
	R other(*this);
	other *= scalar;
	return other;
}

temptensor_trs(T, R, S)
R Tensor<T>::operator/(const S scalar) const {
	ASSERT_DOMAIN(scalar != S(0))
	R other(*this);
	other /= scalar;
	return other;
}


temptensor_tra(T, R, A)
R Tensor<T>::operator+(const A &other) const {
	R result(*this);
	result += other;
	return result;
}

temptensor_tra(T, R, A)
R Tensor<T>::operator-(const A &other) const {
	operator+(-other);
}



temptensor_a(T, A)
void Tensor<T>::operator+=(const A &other) {
	ASSERT_DOMAIN(Size() == other.Size());
	for(size_t i = 0; i < Size(); ++i)
		grid_[i] += other[i];
}

temptensor_a(T, A)
void Tensor<T>::operator-=(const A &other) {
	operator+=(-other);
}


temptensor_s(T, S)
void Tensor<T>::operator+=(const S scalar) {
	for(auto &it : grid_)
		it += scalar;
}

temptensor_s(T, S)
void Tensor<T>::operator-=(const S scalar) {
	operator+=(-scalar);
}

temptensor_s(T, S)
void Tensor<T>::operator*=(const S scalar) {
	for(auto &it : grid_)
		it *= scalar;
}

temptensor_s(T, S)
void Tensor<T>::operator/=(const S scalar) {
	ASSERT_DOMAIN(scalar != S(0));
	operator*=(S(1.) / scalar);
}
