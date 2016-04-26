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


	bool cmp_double(Matrix::val_t a, Matrix::val_t b, const Matrix::val_t PRECISION = 0.00001) {
		if(std::abs(a - b) <= PRECISION)
			return true;
		std::cerr << a << ' ' << b << std::endl;
		return false;
	}

	bool cmp_matr_double(const Matrix &a, const Matrix &b, const Matrix::val_t PRECISION = 0.00001) {
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
};
