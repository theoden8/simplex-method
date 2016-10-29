#include "Operators.hpp"

template <class T>
BinaryOperator<T>::BinaryOperator(T f, T s):
	args(std::make_pair(f, s))
{}

template <class T>
BinaryOperator<T>::operator T() {
	return func()(args.first, args.second);
}
