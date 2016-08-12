#include "MatrixTests.hpp"

TEST_F(MatrixTest, TestingConstructors) {
	Matrix
		A({
			Vector({1, 0, 0, 0, 0}),
			Vector({0, 1, 0, 0, 0}),
			Vector({0, 0, 1, 0, 0}),
			Vector({0, 0, 0, 1, 0}),
			Vector({0, 0, 0, 0, 1})
		}),
		A2(make_mat({
			{1, 0, 0, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 1, 0},
			{0, 0, 0, 0, 1}
		})),
		B(5);
	ASSERT_EQ(A, B);
	ASSERT_EQ(A, A2);
	for(size_t y = 0; y < A.Height(); ++y) {
		for(size_t x = 0; x < A.Width(); ++x) {
			ASSERT_EQ(A[y][x], B[y][x]);
			const real_t val = (y == x);
			ASSERT_EQ(A[y][x], val);
			ASSERT_EQ(B[y][x], val);
		}
	}
	const real_t C_DEFAULT_VALUE = 0;
	Matrix C(5, 10, C_DEFAULT_VALUE), D(5, 10);
	ASSERT_TRUE(C == D);
	for(size_t y = 0; y < C.Height(); ++y) {
		for(size_t x = 0; x < C.Width(); ++x) {
			ASSERT_EQ(C[y][x], C_DEFAULT_VALUE);
			ASSERT_EQ(D[y][x], (real_t)(0));
		}
	}
	/* // checking that constructions of empty matrices does not throw an exception */
	ASSERT_EQ(Matrix(Matrix::matrix_t(0)), Matrix(0, 0, C_DEFAULT_VALUE));
	ASSERT_EQ(Matrix(Matrix::matrix_t(0)), Matrix(0));
}
