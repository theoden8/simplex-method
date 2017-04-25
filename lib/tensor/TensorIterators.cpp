#include "Tensor.hpp"

template <typename T>
typename Tensor<T>::iter_t Tensor<T>::begin() {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.begin();
}

template <typename T>
typename Tensor<T>::iter_t Tensor<T>::end() {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.end();
}


template <typename T>
typename Tensor<T>::const_iter_t Tensor<T>::begin() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.begin();
}

template <typename T>
typename Tensor<T>::const_iter_t Tensor<T>::end() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.end();
}
