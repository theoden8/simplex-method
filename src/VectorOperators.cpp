#include "Vector.hpp"

Vector Vector::operator+ () const {
	return *this;
}

Vector Vector::operator- () const {
	return *this * real_t(-1);
}


Vector Vector::operator+ (const real_t scalar) const {
	Vector A = *this;
	for(size_t i = 0; i < Size(); ++i)
		A[i] += scalar;
	return A;
}

Vector Vector::operator- (const real_t scalar) const {
	return *this + (-scalar);
}

Vector Vector::operator* (const real_t scalar) const {
	Vector A = *this;
	for(size_t i = 0; i < Size(); ++i)
		A[i] *= scalar;
	return A;
}

Vector Vector::operator/ (const real_t scalar) const {
	if(scalar == real_t(0)) {
		throw std::runtime_error("Vector::operator/ Can not divide by zero.");
	}

	return *this * (1 / scalar);
}


Vector Vector::operator+ (const Vector &B) const {
	if(Size() != B.Size()) {
		throw std::runtime_error("Vector::operator+ Vectors have different dimensions.");
	}

	Vector A = *this;

	for(size_t i = 0; i < Size(); ++i)
		A[i] += B[i];

	return A;
}

Vector Vector::operator- (const Vector &B) const {
	return *this + (-B);
}
