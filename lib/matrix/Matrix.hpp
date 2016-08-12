#pragma once

#include <Vector.hpp>

#include <tuple>
#include <vector>

class Matrix {
public:
	typedef std::vector <Vector> matrix_t;
private:
	matrix_t grid_;
public:
	Matrix(const matrix_t &grid);
	Matrix(const size_t x, const size_t y, const real_t value = 0);
	Matrix(const size_t diagonal);
	~Matrix();
	const bool
		operator==(const Matrix &other) const,
		operator!=(const Matrix &other) const;
// MatrixAttributes
	const matrix_t
		&GetGrid() const;
	const bool
		Square() const;
	const size_t
		Width() const,
		Height() const;
	Vector
		&operator[](size_t row);
	const Vector
		&operator[](size_t row) const;
private:
// MatrixTransformations
	Matrix
		MakeSquare() const,
		ConcatenateColumns(const Matrix &B) const,
		ConcatenateRows(const Matrix &B) const,
		SubMatrix(const size_t start, const size_t length) const;
public:
	Matrix
		LowerTriangular() const,
		UpperTriangular() const;
// MatrixLineOperations
	Matrix
		SwapRows(const size_t row1, const size_t row2) const,
		AddToRow(const size_t row1, const size_t row2, const real_t k) const,
		MultiplyRow(const size_t row1, const real_t k) const,
		SwapColumns(const size_t clm1, const size_t clm2) const,
		AddToColumn(const size_t clm1, const size_t clm2, const real_t k) const,
		MultiplyColumn(const size_t clm1, const real_t k) const;
// MatrixOperators
	Matrix
		operator+() const,
		operator-() const,

		operator+(const real_t &scalar) const,
		operator-(const real_t &scalar) const,
		operator*(const real_t &scalar) const,
		operator/(const real_t &scalar) const,

		operator+(const Matrix &B) const,
		operator-(const Matrix &B) const;
// MatrixProperties
	real_t
		Trace() const,
		Det() const;
// MatrixAlgorithms
	Matrix
		operator*(const Matrix &B) const,
		operator%(const Matrix &B) const,
		Transpose() const,
		Invert() const;
	static Matrix
		GaussianElimination(const Matrix &M);
	static std::pair <Matrix, Matrix>
		LUDecomposition(const Matrix &M);
// SimplexMethod
	static Vector
		SimplexMethod(Matrix A, Vector::line_t C);
// Obsolete (to be replaced with gtesting)
	static void
		Print(const Matrix &A, const char *NAME = "", const size_t h_x = -1, const size_t h_y = -1);
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
