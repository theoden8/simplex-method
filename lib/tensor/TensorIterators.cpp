#pragma once

#include "Tensor.hpp"

template <typename T, typename L>
typename Tensor<T, L>::iter_t Tensor<T, L>::begin() {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.begin();
}

template <typename T, typename L>
typename Tensor<T, L>::iter_t Tensor<T, L>::end() {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.end();
}


template <typename T, typename L>
typename Tensor<T, L>::const_iter_t Tensor<T, L>::begin() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.begin();
}

template <typename T, typename L>
typename Tensor<T, L>::const_iter_t Tensor<T, L>::end() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.end();
}
