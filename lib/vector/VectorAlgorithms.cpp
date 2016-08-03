#include <cmath>

#include "Vector.hpp"

real_t Vector::Abs() const {
	real_t scalar = 0;
	for(const auto &it : Map([](real_t it) { return it * it; }).line_)
		scalar += it;
	return sqrt(scalar);
}

// scalar product
real_t Vector::operator^ (const Vector &other) const {
	ASSERT_DOMAIN(Size() == other.Size());

	real_t scalar = 0;
	Vector mapped[2] = {*this, other};
	for(const auto &it : Map(*this, other, std::multiplies <real_t> ()).line_)
		scalar += it;
	return scalar;
}

// dot product
Vector Vector::operator*(const Vector &other) const {
	ASSERT_DOMAIN(Size() == other.Size());

	return Map(*this, other, std::multiplies <real_t>());
}

// cross product
Vector Vector::operator% (const Vector &other) const {
	ASSERT_DOMAIN(other.Size() == Size());
	ASSERT_DOMAIN(
		Size() == 0
		|| Size() == 3
		|| Size() == 7
	);

	if(Size() == 0) {
		return Vector();
	}
	if(Size() == 3) {
		/*
		 * | i j k |
		 * | a b c |
		 * | x y z |
		 * (a, b, c)^T * (x, y, z)^T = (bz - cy, - (az - cx), ay - bx)
		 */
		const real_t
			&a = line_[0], &b = line_[1], &c = line_[2],
			&x = other[0], &y = other[1], &z = other[2];
		return Vector({
			b * z - c * y,
			c * x - a * z,
			a * y - b * x
		});
	}
	if(Size() == 7) {
	}
}
