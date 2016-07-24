#include <cmath>

#include "Vector.hpp"

real_t Vector::Abs() const {
	real_t scalar = 0;
	for(const auto &it : Map([](real_t it) { return it * it; }).line_)
		scalar += it;
	return sqrt(scalar);
}

real_t Vector::operator^(const Vector &other) const {
	ASSERT_DOMAIN(Size() == other.Size());

	real_t scalar = 0;
	Vector mapped[2] = {*this, other};
	for(const auto &it : Map(*this, other, [](real_t a, real_t b){return a * b;}).line_)
		scalar += it;
	return scalar;
}
