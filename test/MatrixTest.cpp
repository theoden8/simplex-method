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
		B(5);
	ASSERT_TRUE(A == B);
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

TEST_F(MatrixTest, TestingGetters) {
	Matrix A({
		Vector({ 13 , 9  , 13 , -12}),
		Vector({ -12, -7 , 4  , 11 }),
		Vector({ 15 , 2  , -11, -4 }),
		Vector({ 11 , 12 , -9 , -4 }),
		Vector({ 13 , -8 , -3 , 8  }),
		Vector({ 0  , 7  , -11, -6 }),
		Vector({ -4 , 0  , 1  , 13 }),
		Vector({ 8  , -1 , -13, 15 }),
		Vector({ 8  , -10, -13, 0  }),
		Vector({ 14 , 13 , 0  , 5  }),
		Vector({ -7 , 0  , -2 , 12 }),
	});
	ASSERT_EQ(11, A.Height());
	ASSERT_EQ(4, A.Width());
	Matrix B(0);
	ASSERT_EQ(0, B.Height());
	ASSERT_EQ(0, B.Width());
	ASSERT_FALSE(A.Square());
	ASSERT_TRUE(Matrix(5).Square());
	for(const auto &m : {A, B}) {
		ASSERT_EQ(m.Height(), m.GetGrid()->size());
		if(!m.Height())
			ASSERT_EQ(m.Width(), 0);
		else
			ASSERT_EQ(m.Width(), m.GetGrid()->front().Size());
		for(size_t y = 0; y < m.Height(); ++y)
			for(size_t x = 0; x < m.Width(); ++x)
				ASSERT_EQ(m[y][x], m[y][x]);
	}
}
