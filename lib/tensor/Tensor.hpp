#pragma once

#include <stdexcept>
#include <vector>
#include <initializer_list>

#include "Types.hpp"

template <size_t N>
class Tensor {
public:
	typedef Tensor <N - 1> subtensor_t;
	typedef std::vector <Tensor <N - 1> > tensor_t;
protected:
	tensor_t grid_;
public:
	Tensor();
	explicit Tensor(size_t size);
	explicit Tensor(size_t size, subtensor_t value);
	explicit Tensor(tensor_t grid);
	virtual ~Tensor();

	virtual Tensor <N - 1> &operator[] (size_t idx) {
		return grid_[idx];
	}

	virtual const Tensor <N - 1> &operator[] (size_t idx) const {
		return grid_[idx];
	}

	virtual size_t Size() const;
	virtual const tensor_t &GetGrid() const;

	virtual void
		Pop(),
		Push(const subtensor_t value),
		Push(const Tensor <N> &other),
		Resize(const size_t new_size, const subtensor_t value);

	virtual operator tensor_t() {
		return grid_;
	}

	virtual Tensor <N>
		operator+() const,
		operator-() const,

		operator+(const Tensor <N> &other) const,
		operator-(const Tensor <N> &other) const,

		operator*(const Tensor <0> &other) const,
		operator/(const Tensor <0> &other) const;
	virtual void
		operator+=(const Tensor <N> &other),
		operator-=(const Tensor <N> &other),
		operator*=(const Tensor <0> &scalar),
		operator/=(const Tensor <0> &scalar);
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

	const operator tensor_t() const {
		return grid_;
	}

	void operator +=(real_t val) {
		grid_ += val;
	}

	void operator -=(real_t val) {
		grid_ -= val;
	}

	void operator *=(real_t val) {
		grid_ *= val;
	}

	void operator /=(real_t val) {
		grid_ /= val;
	}
};
