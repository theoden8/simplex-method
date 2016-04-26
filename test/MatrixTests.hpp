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


	bool cmp_double(real_t a, real_t b, const real_t PRECISION = 0.00001) {
		if(std::abs(a - b) <= PRECISION)
			return true;
		std::cerr << a << ' ' << b << std::endl;
		return false;
	}

	bool cmp_matr_double(const Matrix &a, const Matrix &b, const real_t PRECISION = 0.00001) {
		if(a.Height() != b.Height() || a.Width() != b.Width())
			return false;
		for(size_t y = 0; y < a.Height(); ++y) {
			for(size_t x = 0; x < a.Width(); ++x) {
				if(!cmp_double(a[y][x], b[y][x])) {
					Matrix::Print(a, "a not equal to");
					Matrix::Print(b, "b not equal to");
					return false;
				}
			}
		}
		return true;
	}

    Matrix::matrix_t 2dvector(std::vector <std::vector <real_t> > grid) {
        Matrix::matrix_t m(grid.size());
		for(size_t y = 0; y < grid.size(); ++y)
			m[y] = Vector(m[y]);
	}
};
