#include "VectorTests.hpp"

#include <cmath>

TEST_F(VectorTest, VectorAbsTest) {
	auto ld_sqrt = [](const size_t idx) { return sqrt((real_t)(idx)); };
	Vector
		empty,
		A(100, ld_sqrt),
		B(1000, ld_sqrt);
	ASSERT_EQ(empty.Abs(), 0.);
	ASSERT_TRUE(cmp_double(
		A.Abs(),
		sqrt(
			((A.Size() - 1.) / 2.) * (real_t)A.Size()
		)
	));
	ASSERT_TRUE(cmp_double(
		B.Abs(),
		sqrt(
			((B.Size() - 1.) / 2.) * (real_t)B.Size()
		)
	));
}

TEST_F(VectorTest, VectorScalarMulTest) {
	auto inv = [](const size_t idx) { return 1. / ((real_t)(idx + 1)); };
	Vector
		empty,
		A(100, inv),
		A2(100, 10.),
		B(101, inv);

	ASSERT_EQ(empty ^ empty, 0.);

	ASSERT_ANY_THROW(empty ^ A);
	ASSERT_ANY_THROW(empty ^ B);
	ASSERT_ANY_THROW(A ^ B);

	ASSERT_TRUE(cmp_double(A ^ A2, A2 ^ A));
	ASSERT_TRUE(cmp_double(A ^ A2, 51.87377517639621)); // tested with python
	ASSERT_TRUE(cmp_double(B ^ B, B.Abs() * B.Abs()));
}
