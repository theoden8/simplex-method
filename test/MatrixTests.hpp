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

	bool cmp_matr_double(const Matrix &a, const Matrix &b, const double PRECISION = 0.001) {
		if(a.Height() != b.Height() || a.Width() != b.Width())
			return false;
		for(size_t y = 0; y < a.Height(); ++y) {
			for(size_t x = 0; x < a.Width(); ++x) {
				if(std::abs(a[y][x] - b[y][x]) > PRECISION)
					return false;
				/* std::cerr << a[y][x] << ":" << b[y][x] << "\t"; */
			}
			/* std::cerr << std::endl; */
		}
		return true;
	}
};
