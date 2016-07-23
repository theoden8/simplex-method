#include "Vector.hpp"

Vector Vector::operator+ () const {
	return *this;
}

Vector Vector::operator- () const {
	return *this * real_t(-1);
}


Vector Vector::operator+ (const real_t scalar) const {
	Vector A = *this;
	A.Map([scalar](real_t val) {return val + scalar;});
	return A;
}

Vector Vector::operator- (const real_t scalar) const {
	return *this + (-scalar);
}

Vector Vector::operator* (const real_t scalar) const {
	Vector A = *this;
	A.Map([scalar](real_t val) {return val * scalar;});
	return A;
}

Vector Vector::operator/ (const real_t scalar) const {
	ASSERT_DOMAIN(scalar != real_t(0));

	return *this * (1 / scalar);
}


Vector Vector::operator+ (const Vector &B) const {
	ASSERT_DOMAIN(Size() == B.Size());

	Vector A = *this;
	for(size_t i = 0; i < Size(); ++i)
		A[i] += B[i];
	return A;
}

Vector Vector::operator- (const Vector &B) const {
	return *this + (-B);
}
