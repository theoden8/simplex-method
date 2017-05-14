#pragma once

#include "Tensor.hpp"

template <typename T, typename L> template <typename A>
bool Tensor<T, L>::operator==(const A &other) const {
	if(Size() != other.Size())
		return false;
	for(size_t i = 0; i < Size(); ++i)
		if(!(operator[](i) == other[i]))
			return false;
	return true;
}

template <typename T, typename L> template <typename A>
bool Tensor<T, L>::operator!=(const A &other) const {
	return !operator==(other);
}

template <typename T, typename L> template <typename A>
bool Tensor<T, L>::operator==(const A &&other) const {
	if(Size() != other.Size())
		return false;
	for(size_t i = 0; i < Size(); ++i)
		if(!(operator[](i) == other[i]))
			return false;
	return true;
}

template <typename T, typename L> template <typename A>
bool Tensor<T, L>::operator!=(const A &&other) const {
	return !operator==(other);
}


template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator+() const {
	return *this;
}

template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator-() const {
	Tensor <T, L> other(*this);
	for(auto &it : other)
		it = -it;
	return other;
}


template <typename T, typename L> template <typename A>
decltype(auto) Tensor<T, L>::operator+(const A &other) const {
	decltype(auto) result(*this);
	result += other;
	return result;
}

template <typename T, typename L> template <typename A>
decltype(auto) Tensor<T, L>::operator-(const A &other) const {
	decltype(auto) result(*this);
	result -= other;
	return result;
}


template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator+(const ARG_SUBTENSOR scalar) const {
	decltype(auto) other(*this);
	other += scalar;
	return other;
}

template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator-(const ARG_SUBTENSOR scalar) const {
	operator+(-scalar);
}

template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator*(const ARG_SUBTENSOR scalar) const {
	decltype(auto) other(*this);
	other *= scalar;
	return other;
}

template <typename T, typename L>
decltype(auto) Tensor<T, L>::operator/(const ARG_SUBTENSOR scalar) const {
	ASSERT_DOMAIN(scalar != ARG_SUBTENSOR(0))
	decltype(auto) other(*this);
	other /= scalar;
	return other;
}



template <typename T, typename L> template <typename A>
void Tensor<T, L>::operator+=(const A &other) {
	ASSERT_DOMAIN(Size() == other.Size());
	for(size_t i = 0; i < Size(); ++i)
		operator[](i) += other[i];
}

template <typename T, typename L> template <typename A>
void Tensor<T, L>::operator-=(const A &other) {
	operator+=(-other);
}


template <typename T, typename L>
void Tensor<T, L>::operator+=(const ARG_SUBTENSOR scalar) {
	for(auto &it : *this)
		it += scalar;
}

template <typename T, typename L>
void Tensor<T, L>::operator-=(const ARG_SUBTENSOR scalar) {
	operator+=(-scalar);
}

template <typename T, typename L>
void Tensor<T, L>::operator*=(const ARG_SUBTENSOR scalar) {
	for(auto &it : *this)
		it *= scalar;
}

template <typename T, typename L>
void Tensor<T, L>::operator/=(const ARG_SUBTENSOR scalar) {
	ASSERT_DOMAIN(scalar != ARG_SUBTENSOR(0));
	operator*=(ARG_SUBTENSOR(1.) / scalar);
}
