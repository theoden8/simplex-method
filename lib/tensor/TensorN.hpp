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
	Tensor():
		Tensor(0)
	{}
	explicit Tensor(size_t size);
	explicit Tensor(size_t size, subtensor_t value);
	explicit Tensor(tensor_t grid);
	virtual ~Tensor();

	virtual operator tensor_t();

	virtual Tensor <N - 1> &operator[] (size_t idx);
	virtual const Tensor <N - 1> &operator[] (size_t idx) const;

	virtual size_t
		Size() const;
	virtual const
		tensor_t &GetGrid() const;

	virtual void
		Pop(),
		Push(const subtensor_t value),
		Push(const Tensor <N> &other),
		Resize(const size_t new_size, const subtensor_t value);

	Tensor <N>
		operator+() const,
		operator-() const,

		operator+(const Tensor <0> &scalar) const,
		operator-(const Tensor <0> &scalar) const,
		operator*(const Tensor <0> &scalar) const,
		operator/(const Tensor <0> &scalar) const,

		operator+(const Tensor <N> &other) const,
		operator-(const Tensor <N> &other) const;
	void
		operator+=(const Tensor <N> &other),
		operator-=(const Tensor <N> &other),

		operator+=(const Tensor <0> &scalar),
		operator-=(const Tensor <0> &scalar),
		operator*=(const Tensor <0> &scalar),
		operator/=(const Tensor <0> &scalar);
};
