#include "Matrix.hpp"

Matrix Matrix::MakeSquare() const {
	Matrix result = *this;
	long long diff = Height() - Width();
	if(!diff)
		return result;
	if(diff < 0)
		for(size_t i = 0; i < Height(); ++i)
			result[i].resize(Height());
	if(diff > 0)
		result.grid_.resize(Width());
	return result;
}

Matrix Matrix::ConcatenateColumns(const Matrix &B) const {
	if(Height() != B.Height())
		throw std::runtime_error("Matrix::ConcatenateColumns The matrixes have different heights");
	Matrix A = *this;
	for(size_t y = 0; y < Height(); ++y)
		A[y].insert(A[y].end(), B[y].begin(), B[y].end());
	return A;
}

Matrix Matrix::ConcatenateRows(const Matrix &B) const {
	if(Width() != B.Width())
		throw std::runtime_error("Matrix::ConcatenateRows The matrixes have different widths");
	Matrix A = *this;
	A.grid_.insert(A.grid_.end(), B.grid_.begin(), B.grid_.end());
	return A;
}

Matrix Matrix::SubMatrix(const size_t start, const size_t length) const {
	if(start + length > Width())
		throw std::runtime_error("Matrix::SubMatrix Out of width.");

	Matrix A(matrix_t(Height(), {}));
	for(size_t y = 0; y < Height(); ++y)
		for(size_t x = 0; x < length; ++x)
			A[y].push_back(grid_[y][start + x]);
	return A;
}