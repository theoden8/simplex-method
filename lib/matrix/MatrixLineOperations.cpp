#include "Matrix.hpp"

#include <stdexcept>

Matrix Matrix::SwapRows(const size_t row1, const size_t row2) const {
	ASSERT_DOMAIN(row1 < Height() && row2 < Height());

	Matrix result = *this;
	std::swap(result[row1], result[row2]);
	return result;
}

Matrix Matrix::AddToRow(const size_t row1, const size_t row2, const real_t k = 1) const {
	Matrix result = *this;
	ASSERT_DOMAIN(row1 < Height() && row2 < Height());
	ASSERT_DOMAIN(result[row2].Size() == Width());

	result[row2] = result[row2] + result[row1] * k;
	return result;
}

Matrix Matrix::MultiplyRow(const size_t row1, const real_t k) const {
	ASSERT_DOMAIN(row1 < Height() && k != 0.);
	if(k == 1.)
		return *this;
	return AddToRow(row1, row1, k - 1.);
}


Matrix Matrix::SwapColumns(const size_t clm1, const size_t clm2) const {
	ASSERT_DOMAIN(clm1 < Width() && clm2 < Width());
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		std::swap(result[y][clm1], result[y][clm2]);
	return result;
}

Matrix Matrix::AddToColumn(const size_t clm1, const size_t clm2, const real_t k = 1) const {
	ASSERT_DOMAIN(clm1 < Width() && clm2 < Width());
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][clm2] += result[y][clm1] * k;
	return result;
}

Matrix Matrix::MultiplyColumn(const size_t clm1, const real_t k) const {
	ASSERT_DOMAIN(clm1 < Width() && k != 0.);
	if(k == 1)
		return *this;
	return AddToColumn(clm1, clm1, k - 1);
}
