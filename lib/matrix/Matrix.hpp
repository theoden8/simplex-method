#pragma once

#include <Tensor.hpp>
#include <Vector.hpp>

#include <tuple>
#include <vector>

class Matrix : public Tensor <2> {
public:
	typedef subtensor_t vector_t;
	typedef tensor_t matrix_t;
private:
	matrix_t grid_;
public:
	Matrix();
	explicit Matrix(matrix_t grid);
	explicit Matrix(const size_t x, const size_t y, const real_t value = 0);
	explicit Matrix(const size_t diagonal);
	virtual ~Matrix();
	const bool
		operator==(const Matrix &other) const,
		operator!=(const Matrix &other) const;
// MatrixAttributes
	const bool
		Square() const;
	const size_t
		Width() const,
		Height() const;
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
		operator+(const Matrix &B) const,
		operator-(const Matrix &B) const;
// MatrixProperties
	Vector::scalar_t
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
	static vector_t
		SimplexMethod(Matrix A, vector_t C);
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
