#pragma once

#include <stdexcept>
#include <vector>
#include <type_traits>
#include <iterator>

#include "Types.hpp"

template <class T>
class Tensor {
public:
	typedef std::vector <T> tensor_t;
	/* template <typename S> using SCALAR = typename std::enable_if<std::is_fundamental<S>::value>::type; */
    template <typename S> using SCALAR = S;
	typedef typename std::vector<T>::iterator iter_t;
	typedef typename std::vector<T>::const_iterator const_iter_t;
protected:
	tensor_t grid_;
public:
	Tensor();
	explicit Tensor(size_t size);
	explicit Tensor(size_t size, T value);
	explicit Tensor(tensor_t grid);
	virtual ~Tensor();

	virtual operator tensor_t();

	virtual T &operator[] (size_t idx);
	virtual const T &operator[] (size_t idx) const;

	iter_t
		begin(),
		end();
	const_iter_t
		begin() const,
		end() const;

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

	template <class A>
	bool
		operator==(const A &other) const,
		operator!=(const A &other) const;
	decltype(auto)
		operator+() const,
		operator-() const;
	template <class A>
	decltype(auto)
		operator+(const SCALAR<A> scalar) const,
		operator-(const SCALAR<A> scalar) const,
		operator*(const SCALAR<A> scalar) const,
		operator/(const SCALAR<A> scalar) const;
	template <class A>
	decltype(auto)
		operator+(const A &other) const,
		operator-(const A &other) const;
	template <class A>
	void
		operator+=(const A &other),
		operator-=(const A &other);
	template <class A>
	void
		operator+=(const SCALAR<A> scalar),
		operator-=(const SCALAR<A> scalar),
		operator*=(const SCALAR<A> scalar),
		operator/=(const SCALAR<A> scalar);
};
