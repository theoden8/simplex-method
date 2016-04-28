#pragma once

#include <Matrix.hpp>

#include <cmath>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MatrixTest : public ::testing::Test {
protected:
	MatrixTest() {}
	virtual ~MatrixTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}

	static bool cmp_double(real_t a, real_t b, const real_t PRECISION = 0.00001) {
		if(std::abs(a - b) <= PRECISION)
			return true;
		std::cerr << a << ' ' << b << std::endl;
		return false;
	}

	static bool cmp_matr_double(const Matrix &a, const Matrix &b, const real_t PRECISION = 0.00001) {
		if(a.Height() != b.Height() || a.Width() != b.Width())
			return false;
		for(size_t y = 0; y < a.Height(); ++y) {
			for(size_t x = 0; x < a.Width(); ++x) {
				if(!cmp_double(a[y][x], b[y][x])) {
					Matrix::Print(a, "A : A != B");
					Matrix::Print(b, "B : A != B");
					return false;
				}
			}
		}
		return true;
	}

public:
	static Matrix make_mat(std::vector <std::vector <real_t> > grid) {
		if(grid.size() == 0) {
			return Matrix(0);
		}

		Matrix m(grid.size());
		for(size_t y = 0; y < grid.size(); ++y)
			m[y] = Vector(grid[y]);

		return Matrix(m);
	}
	#define make_mat MatrixTest::make_mat
};
