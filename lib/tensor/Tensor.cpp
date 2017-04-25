#include "Tensor.hpp"

template <typename T>
Tensor<T>::Tensor():
	Tensor(0)
{}

template <typename T>
Tensor<T>::Tensor(size_t size):
	grid_(size)
{}

template <typename T>
Tensor<T>::Tensor(size_t size, T value):
	grid_(size, value)
{}

template <typename T>
Tensor<T>::Tensor(tensor_t grid):
	grid_(grid)
{}

template <typename T>
Tensor<T>::Tensor(size_t size, const std::function <T (size_t)> &construct):
	grid_(size)
{
	size_t i = 0;
	for(auto &x : *this)
		x = construct(i++);
}

template <typename T>
Tensor<T>::~Tensor()
{}
