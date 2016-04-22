#pragma once

#include <utility>
#include <vector>

class Matrix {
public:
	typedef unsigned long size_t;
	typedef long double val_t;
	typedef std::vector <val_t> line_t;
	typedef std::vector <line_t> matrix_t;
private:
	matrix_t grid_;
public:
	Matrix(const matrix_t &grid);
	Matrix(const size_t x, const size_t y, const val_t value = 0);
	Matrix(const size_t diagonal);
	const matrix_t *GetGrid() const;
	const bool operator==(const Matrix &other) const;
	line_t &operator[](size_t row);
	const line_t &operator[](size_t row) const;
	const size_t Width() const;
	const size_t Height() const;
	const bool Square() const;
	const static bool cmp_val_t(const val_t &a, const val_t &b);
private:
// MatrixTransformations
	Matrix MakeSquare() const;
	Matrix ConcatenateColumns(const Matrix &B) const;
	Matrix ConcatenateRows(const Matrix &B) const;
	Matrix SubMatrix(const size_t start, const size_t length) const;
public:
	Matrix LowerTriangular() const;
	Matrix UpperTriangular() const;
public:
// MatrixLineOperations
	Matrix SwapRows(const size_t row1, const size_t row2) const;
	Matrix AddToRow(const size_t row1, const size_t row2, const val_t k) const;
	Matrix MultiplyRow(const size_t row1, const val_t k) const;
	Matrix SwapColumns(const size_t clm1, const size_t clm2) const;
	Matrix AddToColumn(const size_t clm1, const size_t clm2, const val_t k) const;
	Matrix MultiplyColumn(const size_t clm1, const val_t k) const;
// MatrixAlgorithms
	Matrix operator*(const Matrix &B) const;
	Matrix Transpose() const;
	Matrix Invert() const;
	static Matrix GaussianElimination(const Matrix &M);
	std::pair <Matrix, Matrix> LUDecomposition() const;
// SimplexMethod
	static Matrix::line_t SimplexMethod(Matrix A, line_t C);
// Obsolete (to be replaced with gtesting)
	static void Print(const Matrix &A, const char *NAME = "", const size_t h_x = -1, const size_t h_y = -1);
	#if VERBOSE >= 1
		#define _MATRIX_VERBOSE_SELFPRINT(args...) Print(args)
	#else
		#define _MATRIX_VERBOSE_SELFPRINT(args...)
	#endif
	#if VERBOSE >= 2
		#define _MATRIX_VERBOSE_WAITENTER { \
			std::cout << "Press Enter to continue."; \
			std::cin.get(); \
			std::cout << "\033c"; \
		}
	#else
		#define _MATRIX_VERBOSE_WAITENTER
	#endif
	#if VERBOSE == 3
		#define _MATRIX_VERBOSE_LOG(array, pre, str, after) { \
			std::cout << pre; \
			for(const auto &it : array) { \
				std::cout << it << str; \
			} \
		   	std::cout << after; \
		}
	#else
		#define _MATRIX_VERBOSE_LOG
	#endif
};
