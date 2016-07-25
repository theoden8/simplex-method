#include "Vector.hpp"

Vector Vector::operator+ () const {
	return *this;
}

Vector Vector::operator- () const {
	return operator*(real_t(-1));
}


Vector Vector::operator+ (const real_t scalar) const {
	return Map([scalar](real_t val) {return val + scalar;});
}

Vector Vector::operator- (const real_t scalar) const {
	return operator+(-scalar);
}

Vector Vector::operator* (const real_t scalar) const {
	return Map([scalar](real_t val) {return val * scalar;});
}

Vector Vector::operator/ (const real_t scalar) const {
	ASSERT_DOMAIN(scalar != real_t(0));

	return operator*(1 / scalar);
}


Vector Vector::operator+ (const Vector &B) const {
	ASSERT_DOMAIN(Size() == B.Size());

	return Map(*this, B, std::plus <real_t>());
}

Vector Vector::operator- (const Vector &B) const {
	return operator+(-B);
}
