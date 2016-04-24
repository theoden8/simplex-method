#include "Matrix.hpp"

#include <cmath>

#include <stdexcept>

Matrix Matrix::operator* (const Matrix &B) const {
	const Matrix &A = *this;
	if(A.Width() != B.Height())
		throw std::runtime_error("Matrix::Operator* The matrixes have inappropriate dimensions.");

	Matrix C(B.Width(), A.Height(), 0);
	const size_t depth = A.Width();
	for(size_t y = 0; y < A.Height(); ++y)
		for(size_t x = 0; x < B.Width(); ++x)
			for(size_t i = 0; i < depth; ++i)
				C[y][x] += A[y][i] * B[i][x];
	return C;
}

Matrix Matrix::Transpose() const {
	Matrix result(Height(), Width());
	for(size_t x = 0; x < Width(); ++x)
		for(size_t y = 0; y < Height(); ++y)
			result[x][y] = grid_[y][x];
	return result;
}

Matrix Matrix::Invert() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Invert Can not invert non-square matrix.");
	}

	const size_t dim = Height();
	return GaussianElimination(this->ConcatenateColumns(Matrix(dim))).SubMatrix(dim, dim);
}

Matrix Matrix::GaussianElimination(const Matrix &M) {
	if(M.Det() == val_t(0)) {
		throw std::runtime_error("Matrix::GaussianElimination Determinant is zero.");
	}

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

std::tuple <Matrix, Matrix, Matrix> Matrix::LUPDecomposition(const Matrix &M) {
	if(!M.Square()) {
		throw std::runtime_error("Matrix::LUDecomposition Need a square matrix.");
	}

	const size_t dim = M.Height();
	Matrix
		L = M.LowerTriangular(),
		U = M.UpperTriangular(),
		P(dim);

	// pivotize M
	for(size_t x = 0; x < dim; ++x) {

		size_t y_max = 0;
		for(size_t y = x; y < dim; ++y) {
			if(std::abs(M[y_max][x]) < std::abs(M[y][x]))
				y_max = y;
		}

		if(x != y_max)
			P = P.SwapRows(x, y_max);
	}

	for(size_t d = 0; d < dim; ++d) {
		U[d][d] = 0;
	}

	for(size_t i = 0; i < dim; ++i) {
		for(size_t j = i; j < dim; ++j) {
			val_t sum = 0;
			for(size_t k = 0; k < i; ++k)
				sum += L[i][k] * U[k][j];
			L[j][i] = M[j][i] - sum;
		}

		for(size_t j = i; j < dim; ++j) {
			val_t sum = 0;
			for(size_t k = 0; k < i; ++k)
				sum += L[i][k] * U[k][j];
			if(L[i][i] == val_t(0))
				throw std::runtime_error("Matrix::LUDecomposition det(L) tends to 0. Aborting.");
			U[i][j] = (M[j][i] - sum) / L[i][i];
		}
	}

	return std::tuple <Matrix, Matrix, Matrix> (L, U, P);
}
