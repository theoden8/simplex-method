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

TEST_F(VectorTest, VectorScalarOperatorTest) {
	auto sqr = [](const size_t idx) { return (real_t)idx * (real_t)idx; };
	Vector
		empty,
		A(100, sqr),
		B(1000, 10.);
	ASSERT_EQ(empty + 123., empty);
	ASSERT_EQ(empty - 123., empty);
	ASSERT_EQ(empty * 0., empty);
	ASSERT_EQ(empty * -12., empty);
	ASSERT_EQ(empty / -12., empty);
	ASSERT_ANY_THROW(empty / 0.);

	ASSERT_EQ(A * 0., Vector(A.Size(), 0.));
	ASSERT_EQ(B * 0., Vector(B.Size(), 0.));
	ASSERT_ANY_THROW(A / 0.);
	ASSERT_ANY_THROW(B / 0.);

	auto sqr_add_ten = [](const size_t idx) { return (real_t)idx * (real_t)idx + 10.; };
	ASSERT_TRUE(cmp_vec_double(
			A + 10.,
			Vector(A.Size(), sqr_add_ten)
	));
	ASSERT_TRUE(cmp_vec_double(
			B + 10.,
			Vector(B.Size(), 20.)
	));
	auto sqr_sub_ten = [](const size_t idx) { return (real_t)idx * (real_t)idx - 10.; };
	ASSERT_TRUE(cmp_vec_double(
			A - 10.,
			Vector(A.Size(), sqr_sub_ten)
	));
	ASSERT_TRUE(cmp_vec_double(
			B - 10.,
			Vector(B.Size(), 0.)
	));
	auto sqr_div_ten = [](const size_t idx) { return (real_t)idx * (real_t)idx / 10.; };
	ASSERT_TRUE(cmp_vec_double(
			A * .1,
			Vector(A.Size(), sqr_div_ten)
	));
	ASSERT_TRUE(cmp_vec_double(
			B * 10.,
			Vector(B.Size(), 100.)
	));
	ASSERT_TRUE(cmp_vec_double(
			A / 10.,
			Vector(A.Size(), sqr_div_ten)
	));
	ASSERT_TRUE(cmp_vec_double(
			B / 10.,
			Vector(B.Size(), 1.)
	));
}

TEST_F(VectorTest, VectorCalculusTest) {
	auto sqr = [] (const size_t idx) { return (real_t)(idx * idx); };
	auto neg_sqr = [] (const size_t idx) { return -(real_t)(idx * idx); };
	Vector
		empty,
		Asqr(100, sqr),
		Ansqr(100, neg_sqr),
		Bsqr(99, sqr),
		Bnsqr(99, neg_sqr);
	ASSERT_ANY_THROW(empty + Asqr);
	ASSERT_ANY_THROW(empty + Ansqr);
	ASSERT_ANY_THROW(empty + Bsqr);
	ASSERT_ANY_THROW(empty + Bnsqr);
	ASSERT_ANY_THROW(Asqr + Bsqr);
	ASSERT_ANY_THROW(Ansqr + Bnsqr);
	ASSERT_TRUE(cmp_vec_double(Asqr + Ansqr, Ansqr + Asqr));
	ASSERT_TRUE(cmp_vec_double(Asqr + Ansqr, Vector(Asqr.Size(), 0.)));
	ASSERT_TRUE(cmp_vec_double(Bsqr + Bnsqr, Bnsqr + Bsqr));
	ASSERT_TRUE(cmp_vec_double(Bsqr + Bnsqr, Vector(Bsqr.Size(), 0.)));
}
