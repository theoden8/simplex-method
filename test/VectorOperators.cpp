#include "VectorTests.hpp"

TEST_F(VectorTest, VectorUnaryOperatorsTest) {
	Vector
		empty,
		A({5, -3, 54, 1}),
		B({6, -65, 3, 42 , 3, 55, 87});
	ASSERT_EQ(empty, +empty);
	ASSERT_EQ(empty, -empty);
	ASSERT_EQ(A, +A);
	ASSERT_EQ(B, +B);
	ASSERT_TRUE(cmp_vec_double(
			-A, Vector({-5, 3, -54, -1})
	));
	ASSERT_TRUE(cmp_vec_double(
			-B, Vector({-6, 65, -3, -42 , -3, -55, -87})
	));
}
