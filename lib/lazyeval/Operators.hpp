#pragma once

#include "Evaluation.hpp"

#include <functional>

template <class T>
class BinaryOperator : public Evaluation <T, T, T> {
protected:
	typedef std::binary_function <T, T, T> bin_func_t;
	virtual bin_func_t func() = 0;
	std::pair <T, T> args;
public:
	BinaryOperator(T f, T s);
	virtual operator T();
};

template <class T>
class Addition : public BinaryOperator <T> {
	BinaryOperator::bin_func_t func() { return std::plus <T>; }
};

template <class T>
class Subtraction : public BinaryOperator <T> {
	BinaryOperator::bin_func_t func() { return std::minus <T>; }
};

template <class T>
class Multiplication : public BinaryOperator <T> {
	BinaryOperator::bin_func_t func() { return std::multiplies <T>; }
};

template <class T>
class Division : public BinaryOperator <T> {
	BinaryOperator::bin_func_t func() { return std::divides <T>; }
};
