#pragma once

#include <stdexcept>
#include <vector>

typedef unsigned long size_t;
typedef long double real_t;

template <size_t DIM>
class Tensor {
protected:
	typedef std::vector <Tensor <DIM - 1> > tensor_t;
	tensor_t grid;

public:
	Tensor(const tensor_t &);
	virtual ~Tensor();
};


template <>
class Tensor<0> {
protected:
	typedef real_t tensor_t;
public:
	tensor_t grid;
};
