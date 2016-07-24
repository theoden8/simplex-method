#include "VectorTests.hpp"

TEST_F(VectorTest, VectorReverseTest) {
	Vector
		empty,
		A({5, -3, 54, 1}),
		B({6, -65, 3, 42 , 3, 55, 87});
	ASSERT_EQ(empty, empty.Reverse());
	ASSERT_TRUE(cmp_vec_double(
			A.Reverse(),
			Vector({1, 54, -3, 5})
	));
	ASSERT_TRUE(cmp_vec_double(
			B.Reverse(),
			Vector({87, 55, 3, 42, 3, -65, 6})
	));
}
