#pragma once

#include <Vector.hpp>

#include <cmath>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class VectorTest : public ::testing::Test {
protected:
	VectorTest() {}
	virtual ~VectorTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {}

	static bool cmp_double(real_t a, real_t b, const real_t PRECISION = 0.00001) {
		if(
			(a == NAN && b == NAN)
			|| (a == INFINITY && b == INFINITY)
			|| (a == -INFINITY && b == -INFINITY)
			|| (std::abs(a - b) <= PRECISION)
		)
		{
			return true;
		}
		std::cerr << a << ' ' << b << std::endl;
		return false;
	}

	static bool cmp_vec_double(const Vector &a, const Vector &b, const real_t PRECISION = 0.00001) {
		if(a.Size() != b.Size())
			return false;
		for(size_t i = 0; i < a.Size(); ++i) {
			if(!cmp_double(a[i], b[i])) {
				Vector::Print(a);
				Vector::Print(b);
				return false;
			}
		}
		return true;
	}
};
