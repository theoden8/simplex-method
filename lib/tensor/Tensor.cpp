#include "Tensor.hpp"
#include "TensorTemplates.hpp"

template <class T>
Tensor<T>::Tensor():
	Tensor(0)
{}

template <class T>
Tensor<T>::Tensor(size_t size):
	grid_(size)
{}

template <class T>
Tensor<T>::Tensor(size_t size, T value):
	grid_(size, value)
{}

template <class T>
Tensor<T>::Tensor(tensor_t grid):
	grid_(grid)
{}

template <class T>
Tensor<T>::~Tensor()
{}
