#include "MatrixTests.hpp"

Matrix
	empty(0),
	some(make_mat({
		{ -5 , -5, 0 , 11 , 15 },
		{ -4 , -2, 15, -13, 13 },
		{ -10, -2, 14, -12, 1  },
		{ -1 , 12, 12, -3 , -7 },
	})),
	longmatrix(make_mat({
		{13, -15, -7 , 9  , 13, -1, 1, -13},
		{-9, 2  , 4  , -11, 3 , -1, 5, -13},
		{-5, 9  , -14, -2 , 5 , -2, 7, -3 },
		{1 , 3  , -7 , 8  , 11, -1, 4, 14 },
	}));

TEST_F(MatrixTest, MatrixUNARYOperatorsTest) {
	ASSERT_EQ(empty, +empty);
	ASSERT_EQ(empty, -empty);
	ASSERT_EQ(some, +empty);
	ASSERT_EQ(-some, make_mat({
			{ +5 , +5,-0 ,-11 ,-15 },
			{ +4 , +2,-15, +13,-13 },
			{ +10, +2,-14, +12,-1  },
			{ +1 ,-12,-12, +3 , +7 },
	}));
}

TEST_F(MatrixTest, MatrixScalarOperatorsTest) {
	ASSERT_EQ(empty, empty + 1.);
	ASSERT_EQ(empty, empty - 1.);
	ASSERT_EQ(empty, empty * 1.);
	ASSERT_EQ(empty, empty / 1.);
	ASSERT_ANY_THROW(empty / 0.);

	ASSERT_ANY_THROW(some / 0.);
	ASSERT_TRUE(cmp_matr_double(
			some + 10., make_mat({
			{  5 ,  5, 10, 21 , 25 },
			{  6 ,  8, 25,  -3, 23 },
			{  0 ,  8, 24,  -2, 11 },
			{  9 , 22, 22,  7 , 3  },
	})));
	ASSERT_TRUE(cmp_matr_double(
			some - 10., make_mat({
			{ -15,-15,-10,   1,  5 },
			{ -14,-12,  5, -23,  3 },
			{ -20,-12,  4, -22, -9 },
			{ -11,  2,  2, -13,-17 },
	})));
	ASSERT_TRUE(cmp_matr_double(
			some * 0.,
			Matrix(some.Width(), some.Height(), 0)
	));
	ASSERT_TRUE(cmp_matr_double(
			some * 1.,
			some
	));
	ASSERT_TRUE(cmp_matr_double(
			some / 1.,
			some
	));
	ASSERT_TRUE(cmp_matr_double(
			some / 0.5, make_mat({
			{ -10,-10, 0 , 22 , 30 },
			{ -8 , -4, 30, -26, 26 },
			{ -20, -4, 28, -24, 2  },
			{ -2 , 24, 24, -6 , -14},
	})));
}

TEST_F(MatrixTest, MatrixCalculusTest) {
	ASSERT_EQ(empty + empty, empty);
	ASSERT_EQ(empty - empty, empty);

	ASSERT_ANY_THROW(some + longmatrix);
	ASSERT_ANY_THROW(some - longmatrix);

	ASSERT_TRUE(cmp_matr_double(
			some * 2.,
			some + some
	));
	ASSERT_TRUE(cmp_matr_double(
			longmatrix * -2.,
			-longmatrix - longmatrix
	));
}
