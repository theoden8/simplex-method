#pragma once

#include <vector>
#include <functional>

#include <Tensor.hpp>

class Vector : public Tensor <1> {
public:
	typedef subtensor_t scalar_t;
	typedef tensor_t line_t;
	typedef const std::function <scalar_t (scalar_t)> mapfunc_t;
	typedef const std::function <scalar_t (scalar_t, scalar_t)> mapfunc_2_t;
public:
//Vector
	Vector();
	explicit Vector(size_t size, real_t value = 0.);
	explicit Vector(line_t line);
	explicit Vector(size_t size, const std::function <real_t (size_t)> &construct);
	virtual ~Vector();

	const bool
		operator== (const Vector &other)
			const;

	static void
		Print(const Vector &v);

// VectorAttributes
	scalar_t
		First() const,
		Last() const;

// VectorTransformations
	Vector
		Reverse() const;

// VectorFunctional
	static Vector
		Map(const Vector &a, const Vector &b, mapfunc_2_t &map_lambda);
	Vector
		Map(mapfunc_t &map_lambda) const;
	scalar_t
		Reduce(mapfunc_2_t &map_lambda) const;
	// TODO reduce

// VectorOperators
	Vector
		operator+ (const scalar_t scalar) const,
		operator- (const scalar_t scalar) const,
		operator* (const scalar_t scalar) const,
		operator/ (const scalar_t scalar) const,

		operator+ (const Vector &B) const,
		operator- (const Vector &B) const;

// VectorPermutations
	// TODO

// VectorAlgorithms
	scalar_t
		Abs() const,
		operator^ (const Vector &other) const;
	Vector
		operator% (const Vector &other) const;
};
