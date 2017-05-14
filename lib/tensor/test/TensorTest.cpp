#include "TensorTests.hpp"

TEST_F(TensorTest, ImplicitConstructor) {
	Tensor <real_t> a(30.), b(15.);
	//ASSERT_TRUE(cmp_double(a + b, 45.));
	Tensor <Tensor <real_t> > m1(5, Tensor <real_t>(10, 100.));
}
