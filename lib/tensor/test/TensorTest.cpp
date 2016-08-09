#include "TensorTests.hpp"


TEST_F(TensorTest, ImplicitConstructor) {
	Tensor <0> a(30.), b(15.);
	ASSERT_TRUE(cmp_double(a + b, 45.));
}
