#include "MatrixTests.hpp"

#include <cmath>

bool cmp_matr_double(const Matrix &a, const Matrix &b, const double PRECISION = 0.001) {
	if(a.Height() != b.Height() || a.Width() != b.Width())
		return false;
	for(size_t y = 0; y < a.Height(); ++y) {
		for(size_t x = 0; x < a.Width(); ++x) {
			if(std::abs(a[y][x] - b[y][x]) > PRECISION)
				return false;
			/* std::cerr << a[y][x] << ":" << b[y][x] << "\t"; */
		}
		/* std::cerr << std::endl; */
	}
	return true;
}

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

/*
 * Invert and GaussianElimination can not be tested as determinant function is
 * not implemented, and thus there is no point in trying to check their
 * validity. Simplex method implementation uses neither, therefore we are able
 * to verify it (by hand and verifying some aspects of the solution).
 */

struct smethod_args {
	Matrix M;
	Matrix::line_t F;
	smethod_args(Matrix M, Matrix::line_t F):
		M(M), F(F)
	{}
};
static Matrix::line_t sm_wrap(const smethod_args &s) {
	return Matrix::SimplexMethod(s.M, s.F);
}
static char verify_solution_validity(const Matrix &A, const Matrix::line_t &solution, const Matrix::line_t &optimized) {
	// Substitute values into all rows and verify equations
	const static Matrix::val_t PRECISION = 0.001;
	for(int i = 0; i < solution.size() - 1; ++i)
		if(solution[i] < 0)
			return 1;
	for(int y = 0; y < A.Height(); ++y) {
		Matrix::val_t sum = 0;
		for(int x = 0; x < A.Width() - 1; ++x)
			sum += A[y][x] * solution[x];
		if(std::abs(A[y][A.Width() - 1] - sum) > PRECISION)
			return 1;
	}
	return 0;
}
TEST_F(MatrixTest, SimplexMethodTests) {
	// Tested with SageMath
	smethod_args
		no_solutions(
			Matrix({
				{  2, 3, 6 },
				{ -3, 2, 3 },
				{ -3, 2, 5 },
				{  0, 2, 4 },
			}),
			{ 4, 3 }
		),
		solveable(
			Matrix({
				   { 15,-5, 8, 1, -20},
				   { 8 ,-4, 0, 2,  3 },
				   { 6 , 8,-9,-3, 13 },
			}),
			{ 0, -9, -1, 5 }
		);
	ASSERT_ANY_THROW(sm_wrap(no_solutions));
	ASSERT_TRUE(cmp_matr_double(Matrix({sm_wrap(solveable)}), Matrix({{0.125, 7.625, 0., 16.25, -12.625}})));
}
