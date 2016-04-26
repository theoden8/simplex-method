#include "MatrixTests.hpp"

TEST_F(MatrixTest, MatrixTraceTest) {
	Matrix
		identity(100),
		BIG({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		}),
		empty(0),
		square(4, 4, 4.);
	ASSERT_ANY_THROW(BIG.Trace());
	/* ASSERT_TRUE(cmp_double(identity.Trace(), 100.)); */
	/* ASSERT_TRUE(cmp_double(empty.Trace(), 0.)); */
	/* ASSERT_TRUE(cmp_double(square.Trace(), 16.)); */
}
