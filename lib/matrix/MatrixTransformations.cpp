#include "Matrix.hpp"

#include <stdexcept>

Matrix Matrix::MakeSquare() const {
	Matrix result = *this;
	long long diff = Height() - Width();

	if(diff < 0) {
		for(size_t i = 0; i < Height(); ++i)
			result[i].Resize(Height(), 0.);
	} else if(diff > 0) {
		result.grid_.resize(Width());
	}

	return result;
}

Matrix Matrix::ConcatenateColumns(const Matrix &B) const {
	Matrix A = *this;
	ASSERT_DOMAIN(A.Height() == B.Height());

	for(size_t y = 0; y < Height(); ++y)
		A[y].Push(B[y]);
	return A;
}

Matrix Matrix::ConcatenateRows(const Matrix &B) const {
	Matrix A = *this;
	ASSERT_DOMAIN(A.Width() == B.Width());

	A.grid_.insert(A.grid_.end(), B.grid_.begin(), B.grid_.end());
	return A;
}

Matrix Matrix::SubMatrix(const size_t start, const size_t length) const {
	ASSERT_DOMAIN(start + length <= Width());

	Matrix A(matrix_t(Height(), Vector()));
	for(size_t y = 0; y < Height(); ++y)
		for(size_t x = 0; x < length; ++x)
			A[y].Push(grid_[y][start + x]);
	return A;
}

Matrix Matrix::LowerTriangular() const {
	ASSERT_DOMAIN(Square());

	Matrix B(grid_);
	for(size_t x = 1; x < Width(); ++x)
		for(size_t y = 0; y < x; ++y)
			B[y][x] = real_t(0);
	return B;
}

Matrix Matrix::UpperTriangular() const {
	ASSERT_DOMAIN(Square());

	Matrix B(grid_);
	for(size_t y = 1; y < Height(); ++y)
		for(size_t x = 0; x < y; ++x)
			B[y][x] = real_t(0);
	return B;
}
