#pragma once

#include <vector>
#include <functional>

#include <Tensor.hpp>

class Vector : public Tensor <long double> {
public:
	typedef long double scalar_t;
	typedef tensor_t line_t;
	typedef const std::function <scalar_t (scalar_t)> mapfunc_t;
	typedef const std::function <scalar_t (scalar_t, scalar_t)> mapfunc_2_t;
public:
//Vector
	explicit Vector();
	explicit Vector(size_t size, scalar_t value = 0.);
	explicit Vector(line_t line);
	explicit Vector(size_t size, const std::function <scalar_t (size_t)> &construct);
	virtual ~Vector();

	static void
		Print(const Vector &v);

// VectorAttributes
	Vector operator=(Tensor <scalar_t> t);
	Vector operator=(Tensor <scalar_t> &t);
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

// VectorPermutations
	// TODO

// VectorAlgorithms
	scalar_t
		Abs() const,
		operator^ (const Vector &other) const;
	Vector
		operator% (const Vector &other) const;
};
