#include "MatrixTests.hpp"

#include <cmath>

static Matrix
	empty(0),
	det_zero(make_mat({
		{ 20,  28,  8,  4,  32 },
		{ 25,  35, 10,  5,  40 },
		{ 40,  56, 16,  8,  64 },
		{-10, -14, -4, -2, -16 },
		{  0,   0,  0,  0,   0 },
	})),
	invertible(make_mat({
		{   7,  -1,  9,  4,   6},
		{  14, -11,  6,  9,  -8},
		{  -8, -10,  2,  9, -14},
		{ -10,   2,-15, -9,  -4},
		{   0,  -2, 10, -7,  14},
	})),
	longmatrix(make_mat({
		 {13, -15, -7 , 9  , 13, -1, 1, -13},
		 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
		 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
		 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
	}));

TEST_F(MatrixTest, MatrixMultiplicationTest) {
	// Tested with SageMath
	Matrix
		A(5),
		B(6),
		Line({Vector({5, 7, 2, 1, 8})}),
		Column(make_mat({
				{4},
				{5},
				{8},
				{-2},
				{0},
		})),
		BIG1(make_mat({
			{13, -15, -7 , 9  , 13, -1, 1, -13},
			{-9, 2  , 4  , -11, 3 , -1, 5, -13},
			{-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			{1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		})),
		BIG2(make_mat({
			{-4 , 12 , -14},
			{0  , -10, -13},
			{-11, -7 , -13},
			{3  , -11, 5  },
			{-12, 10 , -3 },
			{-1 , 0  , 6  },
			{13 , 0  , 5  },
			{-14, 4  , 10 },
		}));
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
	ASSERT_TRUE(cmp_matr_double(Column * Line, make_mat({
			{ 20,  28,  8,  4,  32 },
			{ 25,  35, 10,  5,  40 },
			{ 40,  56, 16,  8,  64 },
			{-10, -14, -4, -2, -16 },
			{  0,   0,  0,  0,   0 },
	})));
	ASSERT_TRUE(cmp_matr_double(BIG1 * BIG2, make_mat({
			{  92, 334, -21 },
			{ 171, -57,-127 },
			{ 243,   8, 103 },
			{-178, 109, 199 },
	})));
	ASSERT_ANY_THROW(BIG2 * BIG1);
}

TEST_F(MatrixTest, MatrixTranspositionTest) {
	Matrix
		A(10);
	ASSERT_EQ(A.Transpose(), A);
	ASSERT_EQ(empty.Transpose(), empty);
	ASSERT_EQ(det_zero.Transpose(), make_mat({
			{ 20, 25, 40, -10, 0 },
			{ 28, 35, 56, -14, 0 },
			{  8, 10, 16,  -4, 0 },
			{  4,  5,  8,  -2, 0 },
			{ 32, 40, 64, -16, 0 },
	}));
	ASSERT_EQ(longmatrix.Transpose(), make_mat({
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

TEST_F(MatrixTest, MatrixInvertTest) {
	Matrix
		identity(100);
	ASSERT_EQ(empty.Invert(), empty);
	ASSERT_TRUE(cmp_matr_double(identity.Invert(), identity));
	ASSERT_ANY_THROW(det_zero.Invert());
	ASSERT_ANY_THROW(longmatrix.Invert());
	ASSERT_TRUE(cmp_matr_double(
		invertible.Invert(),
		make_mat({
			{-1533./20465, 1073./20465, -2301./40930,  -697./20465,  -159./40930},
			{-5906./20465, -899./20465, -2497./40930, -4394./20465,  -973./40930},
			{-8618./20465,   -2./20465, -1121./40930, -5587./20465,  3071./40930},
			{  2028./4093,  -218./4093,    601./8186,    874./4093,   -887./8186},
			{10382./20465, -672./20465,  3893./81860,  5548./20465, -3253./81860},
		})
	));
}

TEST_F(MatrixTest, MatrixEchelonReducedTest) {
	ASSERT_TRUE(cmp_matr_double(
			det_zero.RowEchelonReduced(),
			make_mat({
				{  1, 1.4, .4, .2, 1.6 },
				{  0,   0,  0,  0,   0 },
				{  0,   0,  0,  0,   0 },
				{  0,   0,  0,  0,   0 },
				{  0,   0,  0,  0,   0 },
			})
	));
	ASSERT_TRUE(cmp_matr_double(
			det_zero.ColumnEchelonReduced(),
			make_mat({
				{   1,   0,  0,  0,  0 },
				{1.25,   0,  0,  0,  0 },
				{   2,   0,  0,  0,  0 },
				{ -.5,   0,  0,  0,  0 },
				{   0,   0,  0,  0,  0 },
			})
	));
	ASSERT_TRUE(cmp_matr_double(
			invertible.RowEchelonReduced(),
			Matrix(invertible.Size())
	));
	ASSERT_TRUE(cmp_matr_double(
			invertible.ColumnEchelonReduced(),
			Matrix(invertible.Size())
	));
	ASSERT_TRUE(cmp_matr_double(
			longmatrix.RowEchelonReduced(),
			make_mat({
				{ 1, 0, 0, 0, -34859./9455, 3531./9455, -16156./9455, -4078./9455},
				{ 0, 1, 0, 0, -34859./9455, 3531./9455, -16156./9455, -4078./9455},
				{ 0, 0, 1, 0,  -8536./9455, 1709./9455,  -5439./9455,  8713./9455},
				{ 0, 0, 0, 1,   3722./1891,  -198./1891,  1065./1891,  3993./1891},
			})
	))
	ASSERT_TRUE(cmp_matr_double(
			longmatrix.ColumnEchelonReduced(),
			make_mat({
				{ 1, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 1, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 1, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 1, 0, 0, 0, 0},
			})
	))
}

TEST_F(MatrixTest, MatrixEchelonReducedTest) {
}

TEST_F(MatrixTest, MatrixGaussianEliminationTest) {
	Matrix
		identity(100);
	ASSERT_EQ(Matrix::GaussianElimination(empty), empty);
	ASSERT_EQ(Matrix::GaussianElimination(identity), identity);
	// TODO fix the following case:
	/* ASSERT_ANY_THROW(Matrix::GaussianElimination(det_zero)); */
}

TEST_F(MatrixTest, MatrixLUDecompositionTest) {
	ASSERT_NO_THROW(Matrix::LUDecomposition(empty));
	ASSERT_ANY_THROW(Matrix::LUDecomposition(longmatrix));
	ASSERT_ANY_THROW(Matrix::LUDecomposition(det_zero));
	ASSERT_NO_THROW(Matrix::LUDecomposition(invertible));
	std::pair <Matrix, Matrix> LU = Matrix::LUDecomposition(invertible);
	Matrix
		L = LU.first,
		U = LU.second;
	ASSERT_TRUE(cmp_matr_double(
			invertible,
			L * U
	));
}

/*
 * GaussianElimination can not be tested as it terminates when the solution
 * matrix is not similar to identity matrix.
 */
