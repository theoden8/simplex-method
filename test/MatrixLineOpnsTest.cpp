#include "MatrixTests.hpp"

#include <stdexcept>
#include <iostream>

TEST_F(MatrixTest, MatrixSwapLinesTest) {
	Matrix
		empty_rows({
			Matrix::line_t(),
			Matrix::line_t(),
			Matrix::line_t()
		}),
		empty(0),
		standard({
			{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
			{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			{21, 22, 23, 24, 25, 26, 27, 28, 29, 20},
			{31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
		});
	ASSERT_EQ(empty_rows, empty_rows.SwapRows(1, 2));
	ASSERT_ANY_THROW(empty.SwapRows(1, 2));
	ASSERT_ANY_THROW(empty.SwapColumns(1, 2));
	ASSERT_EQ(standard.SwapRows(1, 3), Matrix({
			{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
			{31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
			{21, 22, 23, 24, 25, 26, 27, 28, 29, 20},
			{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
	}));
	ASSERT_EQ(standard.SwapColumns(0, 4), Matrix({
			{ 5,  2,  3,  4,  1,  6,  7,  8,  9, 10},
			{15, 12, 13, 14, 11, 16, 17, 18, 19, 20},
			{25, 22, 23, 24, 21, 26, 27, 28, 29, 20},
			{35, 32, 33, 34, 31, 36, 37, 38, 39, 40},
	}));
}

TEST_F(MatrixTest, MatrixAddLinesTest) {
	Matrix
		empty_rows({
			Matrix::line_t(),
			Matrix::line_t(),
			Matrix::line_t()
		}),
		empty(0),
		standard({
			{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
			{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			{21, 22, 23, 24, 25, 26, 27, 28, 29, 20},
			{31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
		});
	ASSERT_ANY_THROW(empty.AddToRow(0, -1, 0));
	ASSERT_ANY_THROW(standard.AddToRow(0, -1, 0));
	ASSERT_ANY_THROW(standard.AddToRow(0, 10, 0));
	ASSERT_ANY_THROW(standard.AddToRow(10, 0, 0));
	ASSERT_ANY_THROW(standard.AddToColumn(0, 10, 0));
	ASSERT_ANY_THROW(standard.AddToColumn(10, 0, 0));
	ASSERT_EQ(empty_rows, empty_rows.AddToRow(1, 1, 0));
	ASSERT_EQ(empty_rows, empty_rows.AddToRow(1, 2, 5));
	ASSERT_EQ(standard.AddToRow(1, 1, -1), Matrix({
			{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{21, 22, 23, 24, 25, 26, 27, 28, 29, 20},
			{31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
	}));
	ASSERT_EQ(standard.AddToRow(1, 2, 0), standard);
}

TEST_F(MatrixTest, MatrixMulLinesTest) {
	Matrix
		empty_rows({
			Matrix::line_t(),
			Matrix::line_t(),
			Matrix::line_t()
		}),
		empty(0),
		standard({
			{ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
			{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
			{21, 22, 23, 24, 25, 26, 27, 28, 29, 20},
			{31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
		});
	// function
	ASSERT_EQ(standard, standard.MultiplyRow(1, 1));
	ASSERT_ANY_THROW(standard.MultiplyColumn(4, 0));
	ASSERT_ANY_THROW(standard.MultiplyRow(3, 0));
}
