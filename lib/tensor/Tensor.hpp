#pragma once

#include <stdexcept>
#include <vector>
#include <initializer_list>

#include "Types.hpp"

template <class T>
class Tensor {
public:
	typedef std::vector <T> tensor_t;
protected:
	tensor_t grid_;
public:
	Tensor():
		Tensor(0)
	{}
	explicit Tensor(size_t size);
	explicit Tensor(size_t size, T value);
	explicit Tensor(tensor_t grid);
	virtual ~Tensor();

	virtual operator tensor_t();

	virtual T &operator[] (size_t idx);
	virtual const T &operator[] (size_t idx) const;

	virtual size_t
		Size() const;
	virtual const
		tensor_t &GetGrid() const;

	virtual void
		Pop(),
		Push(const T value),
		Resize(const size_t new_size, const T value);
	template <class A>
	void
		Push(const A &other);

	template <class R>
	R
		operator+() const,
		operator-() const;
	template <class R, typename S>
	R
		operator+(const S scalar) const,
		operator-(const S scalar) const,
		operator*(const S scalar) const,
		operator/(const S scalar) const;
	template <class R, class A>
	R
		operator+(const A &other) const,
		operator-(const A &other) const;
	template <class A>
	void
		operator+=(const A &other),
		operator-=(const A &other);
	template <typename S>
	void
		operator+=(const S scalar),
		operator-=(const S scalar),
		operator*=(const S scalar),
		operator/=(const S scalar);
};
