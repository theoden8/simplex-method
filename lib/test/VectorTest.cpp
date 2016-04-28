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

TEST_F(VectorTest, VectorGettersTest) {
	auto ld1 = [](const size_t idx) { return (real_t)idx * 10.; };
	Vector
		empty,
		A({1, 2, 3, 4, 5, 6 ,7}),
		B(10, ld1);
	ASSERT_EQ(empty.Size(), 0);
	ASSERT_EQ(A.Size(), 7);
	ASSERT_EQ(B.Size(), 10);
	ASSERT_EQ(Vector(A.GetLine()), Vector({1, 2, 3, 4, 5, 6, 7}));
	ASSERT_EQ(Vector(B.GetLine()), B);
	ASSERT_EQ(Vector(empty.GetLine()), Vector());
	ASSERT_TRUE(cmp_double(B[3], 30.));
	ASSERT_TRUE(cmp_double(B[4], 40.));
	ASSERT_TRUE(cmp_double(B[0], 0.));
	ASSERT_EQ(A[6], 7);
	ASSERT_EQ(A.First(), A[0]);
	ASSERT_EQ(B.First(), B[0]);
	ASSERT_EQ(A.Last(), A[6]);
	ASSERT_EQ(B.Last(), B[9]);
}
