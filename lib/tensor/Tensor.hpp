#pragma once

#include <stdexcept>
#include <iterator>
#include <vector>
#include <functional>
#include <type_traits>

#include "Types.hpp"

template <typename T, typename L = std::vector <T> >
class Tensor {
public:
	typedef L list_t;
	using tensor_t = list_t;
	using ARG_SUBTENSOR = std::conditional_t<std::is_fundamental<T>::value, T, typename std::add_lvalue_reference<T>::type>;
	typedef typename list_t::iterator iter_t;
	typedef typename list_t::const_iterator const_iter_t;
protected:
	tensor_t grid_;
public:
	explicit Tensor();
	explicit Tensor(size_t size);
	explicit Tensor(size_t size, T value);
	explicit Tensor(tensor_t grid);
	explicit Tensor(size_t size, const std::function <T (size_t)> &construct);
	virtual ~Tensor();

	virtual operator tensor_t() const;
	template <typename X> operator X() const;

	virtual T &operator[] (size_t idx);
	virtual const T &operator[] (size_t idx) const;

	iter_t
		begin(),
		end();
	const_iter_t
		begin() const,
		end() const;

	virtual size_t Size() const;
	virtual const tensor_t &GetGrid() const;

	virtual void
		Pop(),
		Push(const T value),
		Resize(const size_t new_size, const T value);
	template <typename A>
	void
		Push(const A &other);

	template <typename A>
	bool
		operator==(const A &other) const,
		operator!=(const A &other) const;
	template <typename A>
	bool
		operator==(const A &&other) const,
		operator!=(const A &&other) const;
	template <typename A>
	decltype(auto)
		operator+(const A &other) const,
		operator-(const A &other) const;
	decltype(auto)
		operator+() const,
		operator-() const;
	decltype(auto)
		operator+(const ARG_SUBTENSOR scalar) const,
		operator-(const ARG_SUBTENSOR scalar) const,
		operator*(const ARG_SUBTENSOR scalar) const,
		operator/(const ARG_SUBTENSOR scalar) const;
	template <typename A>
	void
		operator+=(const A &other),
		operator-=(const A &other);
	void
		operator+=(const ARG_SUBTENSOR scalar),
		operator-=(const ARG_SUBTENSOR scalar),
		operator*=(const ARG_SUBTENSOR scalar),
		operator/=(const ARG_SUBTENSOR scalar);
};

#include "Tensor.cpp"
#include "TensorAttributes.cpp"
#include "TensorIterators.cpp"
#include "TensorOperators.cpp"
#include "TensorTransformations.cpp"
