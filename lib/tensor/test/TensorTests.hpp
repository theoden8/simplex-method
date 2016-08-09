#pragma once

#include <Tensor.hpp>

#include <cmath>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class TensorTest : public ::testing::Test {
protected:
	TensorTest() {}
	virtual ~TensorTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}

	static bool cmp_double(real_t a, real_t b, const real_t PRECISION = 0.00001) {
		if(std::abs(a - b) <= PRECISION)
			return true;
		std::cerr << a << ' ' << b << std::endl;
		return false;
	}
};
