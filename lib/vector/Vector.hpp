#pragma once

#include <vector>
#include <functional>

#include "Types.hpp"

class Vector {
public:
	typedef tensor_t <1> :: type line_t;
	typedef const std::function <real_t (real_t)> mapfunc_t;
	typedef const std::function <real_t (real_t, real_t)> mapfunc_2_t;
private:
	line_t line_;
public:
//Vector
	Vector();
	Vector(size_t size, real_t value);
	Vector(line_t line);
	Vector(size_t size, const std::function <real_t (size_t)> &construct);
	~Vector();

	const bool
		operator== (const Vector &other)
			const;

	static void
		Print(const Vector &v);

// VectorAttributes
	const
		line_t &GetLine()
		const;
	size_t
		Size() const;
	real_t
		First() const,
		Last() const,
		&operator[] (const size_t index);
	const real_t
		&operator[] (const size_t index)
			const;

// VectorTransformations
	void
		Pop(),
		Push(const real_t value),
		Push(const Vector &other),
		Resize(const size_t new_size, const real_t value);
	Vector
		Reverse() const;

// VectorFunctional
	static Vector
		Map(const Vector &a, const Vector &b, mapfunc_2_t &map_lambda);
	Vector
		Map(mapfunc_t &map_lambda) const;
	real_t
		Reduce(mapfunc_2_t &map_lambda) const;
	// TODO reduce,

// VectorOperators
	Vector
		operator+ () const,
		operator- () const,

		operator+ (const real_t scalar) const,
		operator- (const real_t scalar) const,
		operator* (const real_t scalar) const,
		operator/ (const real_t scalar) const,

		operator+ (const Vector &B) const,
		operator- (const Vector &B) const;

// VectorPermutations
	// TODO

// VectorAlgorithms
	real_t
		Abs() const,
		operator^ (const Vector &other) const;
	Vector
		operator* (const Vector &other) const,
		operator% (const Vector &other) const;
};
