#pragma once

#include <vector>
#include <functional>

#include "Types.hpp"

class Vector {
public:
	typedef std::vector <real_t> line_t;
private:
	line_t line_;
public:
	Vector();
	/* Vector(size_t size); */
	Vector(size_t size, real_t value);
	Vector(line_t line);
	Vector(size_t size, const std::function <real_t (size_t)> &construct);
	~Vector();

	const line_t &GetLine() const;
	const bool operator== (const Vector &other) const;

	size_t Size() const;
	real_t First() const;
	real_t Last() const;

	real_t &operator[] (const size_t index);
	const real_t &operator[] (const size_t index) const;

	static void Print(const Vector &v);
// VectorTransformations
	void Push(const real_t value);
	void Push(const Vector &other);
	void Pop();
	void Resize(const size_t new_size, const real_t value);
// VectorFunctional
	void Map(const std::function <real_t (real_t)> &map_lambda);
	// TODO reduce,
// VectorOperators
	// TODO paralellize with map
	Vector operator+ () const;
	Vector operator- () const;

	Vector operator+ (const real_t scalar) const;
	Vector operator- (const real_t scalar) const;
	Vector operator* (const real_t scalar) const;
	Vector operator/ (const real_t scalar) const;

	Vector operator+ (const Vector &B) const;
	Vector operator- (const Vector &B) const;
// VectorPermutations
	// TODO
};
