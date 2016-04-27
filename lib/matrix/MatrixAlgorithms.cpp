#include "Matrix.hpp"

#include <cmath>

#include <stdexcept>

Matrix Matrix::operator* (const Matrix &B) const {
	const Matrix &A = *this;
	if(A.Width() != B.Height()) {
		throw std::runtime_error("Matrix::Operator* The matrixes have inappropriate dimensions.");
	}

	Matrix C(B.Width(), A.Height(), 0);
	Matrix::Print(A, "A");
	Matrix::Print(B, "B");
	const size_t depth = A.Width();

	for(size_t y = 0; y < A.Height(); ++y)
		for(size_t x = 0; x < B.Width(); ++x)
			for(size_t i = 0; i < depth; ++i)
				C[y][x] += A[y][i] * B[i][x];

	return C;
}

Matrix Matrix::Transpose() const {
	Matrix result(Height(), Width());

	for(size_t x = 0; x < Width(); ++x) {
		for(size_t y = 0; y < Height(); ++y)
			result[x][y] = grid_[y][x];
	}

	return result;
}

Matrix Matrix::Invert() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Invert Can not invert non-square matrix.");
	}

	if(Det() == real_t(0)) {
		throw std::runtime_error("Matrix::Invert Det == 0, not invertible");
	}

	const size_t dim = Height();
	return GaussianElimination(this->ConcatenateColumns(Matrix(dim))).SubMatrix(dim, dim);
}

Matrix Matrix::GaussianElimination(const Matrix &M) {
	// TODO: prevent segfault in some cases
	Matrix result = M;

	bool *free = new bool[M.Height()];
	for(size_t i = 0; i < M.Height(); ++i) {
		free[i] = true;
	}

	for(size_t clm = 0; clm < M.Width(); ++clm) {
		for(size_t ln = 0; ln < M.Height(); ++ln)
			if(result[ln][clm] && free[ln]) {
				free[ln] = false;
				result = result.MultiplyRow(ln, 1. / result[ln][clm]);
				for(size_t ln2 = 0; ln2 < M.Height(); ++ln2)
					if(result[ln2][clm] && ln != ln2) {
						result = result.AddToRow(ln, ln2, -result[ln2][clm] / result[ln][clm]);
					}
				break;
			}
	}

	delete free;
	return result;
}

std::pair <Matrix, Matrix> Matrix::LUDecomposition(const Matrix &M) {
	if(!M.Square()) {
		throw std::runtime_error("Matrix::LUDecomposition Need a square matrix.");
	}

	const size_t dim = M.Height();
	Matrix
		L = M.LowerTriangular(),
		U = M.UpperTriangular();

	for(size_t i = 0; i < dim; ++i) {
		U[i][i] = 1;
	}

	for(size_t i = 0; i < dim; ++i) {
		for(size_t j = i; j < dim; ++j) {
			for(size_t k = 0; k < i; ++k)
				L[j][i] -= L[j][k] * U[k][i];
		}

		for(size_t j = i; j < dim; ++j) {
			real_t sum = 0;
			for(size_t k = 0; k < i; ++k)
				sum += L[i][k] * U[k][j];
			if(L[i][i] == real_t(0))
				throw std::runtime_error("Matrix::LUDecomposition det(L) tends to 0. Aborting.");
			U[i][j] = (M[i][j] - sum) / L[i][i];
		}
	}

	return std::pair <Matrix, Matrix> (L, U);
}
