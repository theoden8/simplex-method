#pragma once

#include <stdexcept>
#include <vector>

typedef unsigned long size_t;
typedef long double real_t;

template <size_t N>
class Tensor {
public:
	typedef std::vector <Tensor <N - 1> > tensor_t;
protected:
	tensor_t grid_;

public:
	Tensor();
	Tensor(tensor_t grid);
	Tensor(const tensor_t &grid);
	virtual ~Tensor();

	size_t Size();
	const tensor_t &GetGrid();

	operator tensor_t() {
		return grid_;
	}
};


template <>
class Tensor<0> {
public:
	typedef real_t tensor_t;
protected:
	tensor_t grid_;
public:
	Tensor(tensor_t val):
		grid_(val)
	{}

	const tensor_t &GetGrid() {
		return grid_;
	}

	size_t Size() {
		return 1;
	}

	operator tensor_t() {
		return grid_;
	}
};
