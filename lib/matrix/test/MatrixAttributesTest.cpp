#include "MatrixTests.hpp"

TEST_F(MatrixTest, TestingAttributes) {
	Matrix A({
		Vector({ 13 , 9  , 13 , -12}),
		Vector({ -12, -7 , 4  , 11 }),
		Vector({ 15 , 2  , -11, -4 }),
		Vector({ 11 , 12 , -9 , -4 }),
		Vector({ 13 , -8 , -3 , 8  }),
		Vector({ 0  , 7  , -11, -6 }),
		Vector({ -4 , 0  , 1  , 13 }),
		Vector({ 8  , -1 , -13, 15 }),
		Vector({ 8  , -10, -13, 0  }),
		Vector({ 14 , 13 , 0  , 5  }),
		Vector({ -7 , 0  , -2 , 12 }),
	});
	ASSERT_EQ(11, A.Height());
	ASSERT_EQ(4, A.Width());
	Matrix B(0);
	ASSERT_EQ(0, B.Height());
	ASSERT_EQ(0, B.Width());
	ASSERT_FALSE(A.Square());
	ASSERT_TRUE(Matrix(5).Square());
	for(const auto &m : {A, B}) {
		ASSERT_EQ(m.Height(), m.GetGrid().size());

		if(!m.Height())
			ASSERT_EQ(m.Width(), 0);
		else
			ASSERT_EQ(m.Width(), m.GetGrid().front().Size());

		for(size_t y = 0; y < m.Height(); ++y) {
			for(size_t x = 0; x < m.Width(); ++x)
				ASSERT_EQ(m[y][x], m[y][x]);
		}
	}
}
