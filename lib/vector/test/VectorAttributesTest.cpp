#include "VectorTests.hpp"

TEST_F(VectorTest, VectorAttributesTest) {
	auto ld1 = [](const size_t idx) { return scalar_t(idx) * scalar_t(10); };
	Vector
		empty,
		A({1, 2, 3, 4, 5, 6 ,7}),
		B(10, ld1);
	ASSERT_EQ(empty.Size(), 0);
	ASSERT_EQ(A.Size(), 7);
	ASSERT_EQ(B.Size(), 10);
	ASSERT_EQ(Vector(A.GetGrid()), Vector({1, 2, 3, 4, 5, 6, 7}));
	ASSERT_EQ(Vector(B.GetGrid()), B);
	ASSERT_EQ(Vector(empty.GetGrid()), Vector());
	ASSERT_TRUE(cmp_double(B[3], 30.));
	ASSERT_TRUE(cmp_double(B[4], 40.));
	ASSERT_TRUE(cmp_double(B[0], 0.));
	ASSERT_EQ(A[6], 7);
	ASSERT_EQ(A.First(), A[0]);
	ASSERT_EQ(B.First(), B[0]);
	ASSERT_EQ(A.Last(), A[6]);
	ASSERT_EQ(B.Last(), B[9]);
}
