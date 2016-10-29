#include "Matrix.hpp"


Matrix Matrix::operator+ (const Matrix &B) const {
	Matrix A = *this;
	ASSERT_DOMAIN(A.Width() == B.Width() && A.Height() == B.Height());

	for(size_t y = 0; y < Height(); ++y)
		for(size_t x = 0; x < Width(); ++x)
			A[y][x] += B[y][x];
	return A;
}

Matrix Matrix::operator- (const Matrix &B) const {
	return operator+ (Matrix(-Tensor<2>(B)));
}
