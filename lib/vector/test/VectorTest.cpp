#include "VectorTests.hpp"

TEST_F(VectorTest, VectorConstructorsTest) {
	auto ld1 = [](const size_t idx) { return (real_t)idx * (real_t)idx; };
	Vector
		empty1,
		/* empty2(0), */
		empty3(0, 0.),
		empty4((Vector::line_t())),
		A({1, 1, 1, 1, 1, 1}),
		B(6, 1),
		LD(5, ld1);
	/* ASSERT_EQ(empty1, empty2); */
	ASSERT_EQ(empty3, empty4);
	ASSERT_EQ(empty1, empty3);
	ASSERT_EQ(A, B);
	ASSERT_TRUE(cmp_vec_double(
			LD,
			Vector({0., 1., 4., 9., 16.})
	));
}
