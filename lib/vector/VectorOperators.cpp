#include "Vector.hpp"


Vector Vector::operator+ (const scalar_t scalar) const {
	return Map([scalar](scalar_t val) {return val + scalar;});
}

Vector Vector::operator- (const scalar_t scalar) const {
	return *this + (-scalar);
}

Vector Vector::operator* (const scalar_t scalar) const {
	return Map([scalar](scalar_t val) {return val * scalar;});
}

Vector Vector::operator/ (const scalar_t scalar) const {
	ASSERT_DOMAIN(scalar != scalar_t(0));
	return operator*(scalar_t(1) / scalar);
}


Vector Vector::operator+ (const Vector &B) const {
	ASSERT_DOMAIN(Size() == B.Size());
	return Map(*this, B, std::plus <scalar_t>());
}

Vector Vector::operator- (const Vector &B) const {
	return *this + Vector(Tensor<1>(B).operator-());
}
