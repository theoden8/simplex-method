#include "Matrix.hpp"

#include <stdexcept>

Matrix Matrix::SwapRows(const size_t r1, const size_t r2) const {
	ASSERT_DOMAIN(r1 < Height() && r2 < Height());

	Matrix result = *this;
	std::swap(result[r1], result[r2]);
	return result;
}

Matrix Matrix::AddToRow(const size_t r1, const size_t r2, const scalar_t k = 1) const {
	Matrix result = *this;
	ASSERT_DOMAIN(r1 < Height() && r2 < Height());
	ASSERT_DOMAIN(result[r2].Size() == Width());

	result[r2] += result[r1] * k;
	return result;
}

Matrix Matrix::MultiplyRow(const size_t r1, const scalar_t k) const {
	ASSERT_DOMAIN(r1 < Height() && k != 0.);
	if(k == 1.)
		return *this;
	return AddToRow(r1, r1, k - 1.);
}


Matrix Matrix::SwapColumns(const size_t c1, const size_t c2) const {
	ASSERT_DOMAIN(c1 < Width() && c2 < Width());
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		std::swap(result[y][c1], result[y][c2]);
	return result;
}

Matrix Matrix::AddToColumn(const size_t c1, const size_t c2, const scalar_t k = 1) const {
	ASSERT_DOMAIN(c1 < Width() && c2 < Width());
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][c2] += result[y][c1] * k;
	return result;
}

Matrix Matrix::MultiplyColumn(const size_t c1, const scalar_t k) const {
	ASSERT_DOMAIN(c1 < Width() && k != 0.);
	if(k == 1)
		return *this;
	return AddToColumn(c1, c1, k - 1);
}
