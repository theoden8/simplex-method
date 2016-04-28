#include <cmath>

#include "Vector.hpp"

real_t Vector::Abs() const {
	real_t scalar = 0;
	for(size_t i = 0; i < Size(); ++i)
		scalar += line_[i] * line_[i];
	return sqrt(scalar);
}

real_t Vector::operator^(const Vector &other) const {
	ASSERT_DOMAIN(Size() == other.Size());

	real_t scalar = 0;
	for(size_t i = 0; i < Size(); ++i)
		scalar += line_[i] * other[i];
	return scalar;
}
