#include <cmath>

#include "Vector.hpp"

Vector::scalar_t Vector::Abs() const {
	scalar_t scalar = 0;
	for(const auto &it : Map([](scalar_t it) { return it * it; }).grid_)
		scalar += it;
	return sqrt(scalar);
}

// dot product
Vector::scalar_t Vector::operator^ (const Vector &other) const {
	ASSERT_DOMAIN(Size() == other.Size());

	scalar_t scalar = 0;
	Vector mapped[2] = {*this, other};
	for(const auto &it : Map(*this, other, std::multiplies <scalar_t> ()).grid_)
		scalar += it;
	return scalar;
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
	else if(Size() == 3) {
		/*
		 * | i j k |
		 * | a b c |
		 * | x y z |
		 * (a, b, c)^T * (x, y, z)^T = (bz - cy, - (az - cx), ay - bx)
		 */
		const scalar_t
			&a = grid_[0], &b = grid_[1], &c = grid_[2],
			&x = other[0], &y = other[1], &z = other[2];
		return Vector({
			b * z - c * y,
			c * x - a * z,
			a * y - b * x
		});
	}
	else if(Size() == 7) {
		throw std::logic_error("not implemented yet");
		// TODO
	}
}
