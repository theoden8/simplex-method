#include "MatrixTests.hpp"

#include <cmath>

TEST_F(MatrixTest, MatrixMultiplicationTest) {
	// Tested with SageMath
	Matrix
		A(5),
		B(6),
		Line({{5, 7, 2, 1, 8}}),
		Column({
			   {4},
			   {5},
			   {8},
			   {-2},
			   {0},
		}),
		BIG1({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		}),
		BIG2({
			 {-4 , 12 , -14},
			 {0  , -10, -13},
			 {-11, -7 , -13},
			 {3  , -11, 5  },
			 {-12, 10 , -3 },
			 {-1 , 0  , 6  },
			 {13 , 0  , 5  },
			 {-14, 4  , 10 },
		}),
		empty(0)
	;
	ASSERT_ANY_THROW(A * B);
	ASSERT_ANY_THROW(B * A);
	ASSERT_ANY_THROW(A * Line);
	ASSERT_ANY_THROW(B * Line);
	ASSERT_TRUE(cmp_matr_double(empty * empty, empty));
	ASSERT_TRUE(cmp_matr_double(Line * A, Line));
	ASSERT_TRUE(cmp_matr_double(A * Column, Column));
	ASSERT_TRUE(cmp_matr_double(A * Column, Column));
	ASSERT_ANY_THROW(B * Column);
	ASSERT_ANY_THROW(Column * B);
	ASSERT_TRUE(cmp_matr_double(Line * Column, Matrix(1, 1, 69)));
	ASSERT_TRUE(cmp_matr_double(Column * Line, Matrix({
			{ 20,  28,  8,  4,  32 },
			{ 25,  35, 10,  5,  40 },
			{ 40,  56, 16,  8,  64 },
			{-10, -14, -4, -2, -16 },
			{  0,   0,  0,  0,   0 },
	})));
	ASSERT_TRUE(cmp_matr_double(BIG1 * BIG2, Matrix({
			{  92, 334, -21 },
			{ 171, -57,-127 },
			{ 243,   8, 103 },
			{-178, 109, 199 },
	})));
	ASSERT_ANY_THROW(BIG2 * BIG1);
}

TEST_F(MatrixTest, MatrixTranspositionTest) {
	Matrix
		A(10),
		empty(0),
		square({
				{ 20,  28,  8,  4,  32 },
				{ 25,  35, 10,  5,  40 },
				{ 40,  56, 16,  8,  64 },
				{-10, -14, -4, -2, -16 },
				{  0,   0,  0,  0,   0 },
		}),
		longmatrix({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		});
	ASSERT_EQ(A.Transpose(), A);
	ASSERT_EQ(empty.Transpose(), empty);
	ASSERT_EQ(square.Transpose(), Matrix({
			{ 20, 25, 40, -10, 0 },
			{ 28, 35, 56, -14, 0 },
			{  8, 10, 16,  -4, 0 },
			{  4,  5,  8,  -2, 0 },
			{ 32, 40, 64, -16, 0 },
	}));
	ASSERT_EQ(longmatrix.Transpose(), Matrix({
			{  13,  -9,  -5,  1 },
			{ -15,   2,   9,  3 },
			{  -7,   4, -14, -7 },
			{   9, -11,  -2,  8 },
			{  13,   3,   5, 11 },
			{  -1,  -1,  -2, -1 },
			{   1,   5,   7,  4 },
			{ -13, -13,  -3, 14 },
	}));
}

TEST_F(MatrixTest, MatrixLUDecompositionTest) {
	Matrix
		empty(0),
		det_zero({
				{ 20,  28,  8,  4,  32 },
				{ 25,  35, 10,  5,  40 },
				{ 40,  56, 16,  8,  64 },
				{-10, -14, -4, -2, -16 },
				{  0,   0,  0,  0,   0 },
		}),
		inversible({
				{   7,  -1,  9,  4,   6},
				{  14, -11,  6,  9,  -8},
				{  -8, -10,  2,  9, -14},
				{ -10,   2,-15, -9,  -4},
				{   0,  -2, 10, -7,  14},
		}),
		longmatrix({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		});
	ASSERT_NO_THROW(empty.LUDecomposition());
	ASSERT_ANY_THROW(longmatrix.LUDecomposition());
	ASSERT_ANY_THROW(det_zero.LUDecomposition());
	std::pair <Matrix, Matrix> LU = inversible.LUDecomposition();
	Matrix::Print(LU.first, "Lower");
	Matrix::Print(LU.second, "Upper");
	Matrix::Print(LU.first * LU.second, "L * U");
	ASSERT_TRUE(cmp_matr_double(
			inversible,
			LU.first * LU.second
	));
}

/*
 * Invert and GaussianElimination can not be tested as determinant function is
 * not implemented, and thus there is no point in trying to check their
 * validity. Simplex method implementation uses neither, therefore we are able
 * to verify it (by hand and verifying some aspects of the solution).
 */
