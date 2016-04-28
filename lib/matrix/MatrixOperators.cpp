#include "Matrix.hpp"


Matrix Matrix::operator+ () const {
	return *this;
}

Matrix Matrix::operator- () const {
	return operator*(-1.);
}


Matrix Matrix::operator+ (const real_t &scalar) const {
	Matrix A = *this;
	for(size_t y = 0; y < A.Height(); ++y)
		A[y] = A[y] + scalar;
	return A;
}

Matrix Matrix::operator- (const real_t &scalar) const {
	return operator+ (-scalar);
}

Matrix Matrix::operator* (const real_t &scalar) const {
	Matrix A = *this;
	for(size_t y = 0; y < A.Height(); ++y)
		A[y] = A[y] * scalar;
	return A;
}

Matrix Matrix::operator/ (const real_t &scalar) const {
	ASSERT_DOMAIN(scalar != 0.);
	return operator* (1 / scalar);
}


Matrix Matrix::operator+ (const Matrix &B) const {
	Matrix A = *this;
	ASSERT_DOMAIN(A.Width() == B.Width() && A.Height() == B.Height());

	for(size_t y = 0; y < Height(); ++y)
		A[y] = A[y] + B[y];
	return A;
}

Matrix Matrix::operator- (const Matrix &B) const {
	return operator+ (-B);
}
