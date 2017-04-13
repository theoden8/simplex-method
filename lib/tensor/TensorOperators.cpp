#include "Tensor.hpp"
#include "TensorTemplates.hpp"


template <class T> template <class A>
bool Tensor<T>::operator==(const A &other) const {
	if(Size() != other.Size())
		return false;
	for(size_t i = 0; i < Size(); ++i)
		if(!(*this[i] == other[i]))
			return false;
	return true;
}

template <class T> template <class A>
bool Tensor<T>::operator!=(const A &other) const {
	return !operator==(other);
}


template <class T>
decltype(auto) Tensor<T>::operator+() const {
	return *this;
}

template <class T>
decltype(auto) Tensor<T>::operator-() const {
	Tensor <T> other(*this);
	for(auto &it : other)
		it = -it;
	return other;
}



template <class T> template <class A>
decltype(auto) Tensor<T>::operator+(const SCALAR<A> scalar) const {
	decltype(auto) other(*this);
	other += scalar;
	return other;
}

template <class T> template <class A>
decltype(auto) Tensor<T>::operator-(const SCALAR<A> scalar) const {
	operator+(-scalar);
}

template <class T> template <class A>
decltype(auto) Tensor<T>::operator*(const SCALAR<A> scalar) const {
	decltype(auto) other(*this);
	other *= scalar;
	return other;
}

template <class T> template <class A>
decltype(auto) Tensor<T>::operator/(const SCALAR<A> scalar) const {
	ASSERT_DOMAIN(scalar != SCALAR<A>(0))
	decltype(auto) other(*this);
	other /= scalar;
	return other;
}


template <class T> template <class A>
decltype(auto) Tensor<T>::operator+(const A &other) const {
	decltype(auto) result(*this);
	result += other;
	return result;
}

template <class T> template <class A>
decltype(auto) Tensor<T>::operator-(const A &other) const {
	operator+(-other);
}



template <class T> template <class A>
void Tensor<T>::operator+=(const A &other) {
	ASSERT_DOMAIN(Size() == other.Size());
	for(size_t i = 0; i < Size(); ++i)
		*this[i] += other[i];
}

template <class T> template <class A>
void Tensor<T>::operator-=(const A &other) {
	operator+=(-other);
}


template <class T> template <class A>
void Tensor<T>::operator+=(const SCALAR<A> scalar) {
	for(auto &it : *this)
		it += scalar;
}

template <class T> template <class A>
void Tensor<T>::operator-=(const SCALAR<A> scalar) {
	operator+=(-scalar);
}

template <class T> template <class A>
void Tensor<T>::operator*=(const SCALAR<A> scalar) {
	for(auto &it : *this)
		it *= scalar;
}

template <class T> template <class A>
void Tensor<T>::operator/=(const SCALAR<A> scalar) {
	ASSERT_DOMAIN(scalar != SCALAR<A>(0));
	operator*=(SCALAR<A>(1.) / scalar);
}
