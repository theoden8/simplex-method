#pragma once

#include "Matrix.hpp"

#include <cmath>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MatrixTest : public ::testing::Test {
protected:
	MatrixTest() {}
	virtual ~MatrixTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {
		std::cout << "\n---------------------TEAR DOWN-------------------\n" << std::endl;
	}


	bool cmp_double(Matrix::val_t a, Matrix::val_t b, const Matrix::val_t PRECISION = 0.00001) {
		std::cerr << a << ' ' << b << std::endl;
		return std::abs(a - b) <= PRECISION;
	}

	bool cmp_matr_double(const Matrix &a, const Matrix &b, const Matrix::val_t PRECISION = 0.00001) {
		if(a.Height() != b.Height() || a.Width() != b.Width())
			return false;
		for(size_t y = 0; y < a.Height(); ++y) {
			for(size_t x = 0; x < a.Width(); ++x) {
				if(!cmp_double(a[y][x], b[y][x]))
					return false;
			}
		}
		return true;
	}
};
