#include "MatrixTests.hpp"

Matrix
	empty(0),
	nonsquare(make_mat({
		{13, -15, -7 , 9  , 13, -1, 1, -13},
		{-9, 2  , 4  , -11, 3 , -1, 5, -13},
		{-5, 9  , -14, -2 , 5 , -2, 7, -3 },
		{1 , 3  , -7 , 8  , 11, -1, 4, 14 },
	})),
	column({
		Vector({4}),
		Vector({5}),
		Vector({8}),
		Vector({-2}),
		Vector({0}),
	}),
	identity(10),
	square(make_mat({
		{ 20, 25, 40, -10, 5 },
		{ 28, 35, 56, -14, 4 },
		{  8, 10, 16,  -4, 3 },
		{  4,  5,  8,  -2, 2 },
		{ 32, 40, 64, -16, 1 },
	}));

TEST_F(MatrixTest, MatrixLowerTriangularTest) {
	ASSERT_ANY_THROW(nonsquare.LowerTriangular());
	ASSERT_ANY_THROW(column.LowerTriangular());
	ASSERT_EQ(empty.LowerTriangular(), empty);
	ASSERT_EQ(identity.LowerTriangular(), identity);
	ASSERT_EQ(
		square.LowerTriangular(),
		make_mat({
			{ 20,  0,  0,   0, 0 },
			{ 28, 35,  0,   0, 0 },
			{  8, 10, 16,   0, 0 },
			{  4,  5,  8,  -2, 0 },
			{ 32, 40, 64, -16, 1 },
		})

	);
}

TEST_F(MatrixTest, MatrixUpperTriangularTest) {
	ASSERT_ANY_THROW(nonsquare.UpperTriangular());
	ASSERT_ANY_THROW(column.UpperTriangular());
	ASSERT_EQ(empty.UpperTriangular(), empty);
	ASSERT_EQ(identity.UpperTriangular(), identity);
	ASSERT_EQ(
		square.UpperTriangular(),
		make_mat({
			{ 20, 25, 40, -10, 5 },
			{  0, 35, 56, -14, 4 },
			{  0,  0, 16,  -4, 3 },
			{  0,  0,  0,  -2, 2 },
			{  0,  0,  0,   0, 1 },
		})
	);
}
