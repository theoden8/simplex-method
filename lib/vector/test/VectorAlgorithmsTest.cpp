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

TEST_F(VectorTest, VectorScalarProductTest) {
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

TEST_F(VectorTest, VectorDotProductTest) {
	auto builder = [](const size_t idx) { return (real_t)(idx * idx) / log(real_t(idx + 1)); };
	Vector
		empty,
		A(100, builder),
		A2(100, 10.),
		B(101, builder);

	ASSERT_EQ(empty * empty, empty);
	auto builder2 = [builder](const size_t idx) { return builder(idx) * 10.; };
	ASSERT_TRUE(cmp_vec_double(A * A2, Vector(100, builder2)));
	ASSERT_ANY_THROW(A * B);
	ASSERT_ANY_THROW(A2 * B);
	ASSERT_TRUE(cmp_vec_double(A * A2, A2 * A));
}

TEST_F(VectorTest, VectorCrossProductTest) {
	Vector
		empty,
		three1({4, 12, -5}),
		three2({6, -4, 3}),
		five(5, 1),
		seven1({-3, 2, 4, 3, 5, 2, 14}),
		seven2({4, -1, 2, 0, 6, 4, -6});
	ASSERT_EQ(empty, empty % empty);
	ASSERT_ANY_THROW(three1 % empty);
	ASSERT_ANY_THROW(three1 % five);
	ASSERT_ANY_THROW(three2 % five);
	ASSERT_ANY_THROW(five % five);
	ASSERT_ANY_THROW(three2 % seven1);

	/* ASSERT_TRUE(cmp_vec_double(three1 % three2, three2 % three1)); */
	/* ASSERT_TRUE(cmp_vec_double(three1 % three2, Vector({-16, 42, 88}))); // sage */

	/* ASSERT_TRUE(cmp_vec_double(seven1 % seven2, -(seven2 % seven1))); */
	/* ASSERT_TRUE(cmp_vec_double(seven1 % seven2, Vector({-41, -42, 33, -131, 46, -46, 6}))); // sage */
}
