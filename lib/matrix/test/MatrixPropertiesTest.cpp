#include "MatrixTests.hpp"

static Matrix
	empty(0),
	identity(100),
	BIG = make_mat({
		 {13, -15, -7 , 9  , 13, -1, 1, -13},
		 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
		 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
		 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
	}),
	square(4, 4, 4.),
	det_0 = make_mat({
			{ 20,  28,  8,  4,  32 },
			{ 25,  35, 10,  5,  40 },
			{ 40,  56, 16,  8,  64 },
			{-10, -14, -4, -2, -16 },
			{  0,   0,  0,  0,   0 },
	}),
	inversible = make_mat({
			{   7,  -1,  9,  4,   6},
			{  14, -11,  6,  9,  -8},
			{  -8, -10,  2,  9, -14},
			{ -10,   2,-15, -9,  -4},
			{   0,  -2, 10, -7,  14},
	}),
	longmatrix(make_mat({
		 {13, -15, -7 , 9  , 13, -1, 1, -13},
		 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
		 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
		 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
	}));

TEST_F(MatrixTest, MatrixTraceTest) {
	ASSERT_ANY_THROW(BIG.Trace());
	ASSERT_TRUE(cmp_double(identity.Trace(), 100.));
	ASSERT_TRUE(cmp_double(empty.Trace(), 0.));
	ASSERT_TRUE(cmp_double(square.Trace(), 16.));
}

TEST_F(MatrixTest, MatrixDeterminantTest) {
	ASSERT_ANY_THROW(longmatrix.Det());
	ASSERT_TRUE(cmp_double(identity.Det(), 1.));
	ASSERT_TRUE(cmp_double(empty.Det(), 1.));
	ASSERT_TRUE(cmp_double(det_0.Det(), 0.));
	ASSERT_TRUE(cmp_double(inversible.Det(), -81860.));
}
