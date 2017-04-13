#include "Tensor.hpp"

template <class T>
typename Tensor<T>::iter_t Tensor<T>::begin() {
	ASSERT_DOMAIN(Size() > 0);
	return iter_t(this, 0);
}

template <class T>
typename Tensor<T>::iter_t Tensor<T>::end() {
	ASSERT_DOMAIN(Size() > 0);
	return iter_t(this, Size());
}


template <class T>
typename Tensor<T>::const_iter_t Tensor<T>::begin() const {
	ASSERT_DOMAIN(Size() > 0);
	return const_iter_t(this, 0);
}

template <class T>
typename Tensor<T>::const_iter_t Tensor<T>::end() const {
	ASSERT_DOMAIN(Size() > 0);
	return const_iter_t(this, Size());
}
