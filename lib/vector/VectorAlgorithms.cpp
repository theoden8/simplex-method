#include <cmath>

#include "Vector.hpp"

real_t Vector::abs() const {
	real_t scalar = 0;
	for(size_t i = 0; i < Size(); ++i)
		scalar += line_[i] * line_[i];

	return sqrt(scalar);
}

real_t Vector::operator^(const Vector &other) const {
	if(Size() != other.Size()) {
		throw std::runtime_error("Vector::operator^ need vectors of the same size.");
	}

	real_t scalar = 0;
	for(size_t i = 0; i < Size(); ++i)
		scalar += line_[i] * other[i];

	return scalar;
}
