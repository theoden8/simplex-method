#include "Matrix.hpp"

#include <stdexcept>

Matrix Matrix::SwapRows(const size_t row1, const size_t row2) const {
	if(row1 >= Height() || row2 >= Height()) {
		throw std::runtime_error("Matrix::SwapRows row number out of height.");
	}

	Matrix result = *this;
	std::swap(result[row1], result[row2]);
	return result;
}

Matrix Matrix::AddToRow(const size_t row1, const size_t row2, const real_t k = 1) const {
	Matrix result = *this;
	if(row1 >= Height() || row2 >= Height()) {
		throw std::runtime_error("Matrix::AddToRow row number out of height.");
	} else if(result[row2].Size() != Width()) {
		throw std::runtime_error("Matrix::AddToRow Improper size of a row passed..");
	}

	result[row2] = result[row2] + result[row1] * k;
	return result;
}

Matrix Matrix::MultiplyRow(const size_t row1, const real_t k) const {
	if(row1 >= Height())
		throw std::runtime_error("Matrix::MultiplyRow row number out of height.");
	if(!k)
		throw std::runtime_error("Matrix::MultiplyRow Can't multiply by 0.");
	if(k == 1)
		return *this;

	return AddToRow(row1, row1, k - 1.);
}

Matrix Matrix::SwapColumns(const size_t clm1, const size_t clm2) const {
	if(clm1 >= Width() || clm2 >= Width())
		throw std::runtime_error("Matrix::SwapColumns col number out of height.");
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		std::swap(result[y][clm1], result[y][clm2]);
	return result;
}

Matrix Matrix::AddToColumn(const size_t clm1, const size_t clm2, const real_t k = 1) const {
	if(clm1 >= Width() || clm2 >= Width())
		throw std::runtime_error("Matrix::AddToColumn col number out of height.");
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][clm2] += result[y][clm1] * k;
	return result;
}

Matrix Matrix::MultiplyColumn(const size_t clm1, const real_t k) const {
	if(clm1 >= Width())
		throw std::runtime_error("Matrix::MultiplyColumn col number out of height.");
	else if(!k)
		throw std::runtime_error("Matrix::MultiplyColumn Can't multiply by 0.");
	if(k == 1)
		return *this;
	return AddToColumn(clm1, clm1, k - 1);
}
