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
			a == b
			|| (isnan(a) && isnan(b))
			|| (std::abs(a - b) <= PRECISION)
		)
		{
			return true;
		}
		std::cerr << "not equal: " << a << ' ' << b << std::endl;
		return false;
	}

	static bool cmp_vec_double(const Vector &a, const Vector &b, const real_t PRECISION = 0.00001) {
		if(a.Size() != b.Size())
			return false;
		for(size_t i = 0; i < a.Size(); ++i) {
			if(!cmp_double(a[i], b[i])) {
				std::cout << a.Size() << " " << b.Size() << std::endl;
				Vector::Print(a);
				Vector::Print(b);
				return false;
			}
		}
		return true;
	}
};
