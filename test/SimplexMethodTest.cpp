#include "MatrixTests.hpp"

#include <cmath>

struct smethod_args {
	Matrix M;
	Matrix::line_t F;
	smethod_args(Matrix M, Matrix::line_t F):
		M(M), F(F)
	{}
};

static Matrix::line_t sm_wrap(const smethod_args &s) {
	return Matrix::SimplexMethod(s.M, s.F);
}

static char verify_solution_validity(const Matrix &A, const Matrix::line_t &solution, const Matrix::line_t &optimized) {
	// Substitute values into all rows and verify equations
	const static real_t PRECISION = 0.001;
	for(int i = 0; i < solution.size() - 1; ++i)
		if(solution[i] < 0)
			return 1;
	for(int y = 0; y < A.Height(); ++y) {
		real_t sum = 0;
		for(int x = 0; x < A.Width() - 1; ++x)
			sum += A[y][x] * solution[x];
		if(std::abs(A[y][A.Width() - 1] - sum) > PRECISION)
			return 1;
	}
	return 0;
}

TEST_F(MatrixTest, SimplexMethodTests) {
	// Tested with SageMath
	smethod_args
		no_solutions(
			Matrix({
				{  2, 3, 6 },
				{ -3, 2, 3 },
				{ -3, 2, 5 },
				{  0, 2, 4 },
			}),
			{ 4, 3 }
		),
		solveable(
			Matrix({
				   { 15,-5, 8, 1, -20},
				   { 8 ,-4, 0, 2,  3 },
				   { 6 , 8,-9,-3, 13 },
			}),
			{ 0, -9, -1, 5 }
		);
	ASSERT_ANY_THROW(sm_wrap(no_solutions));
	ASSERT_TRUE(cmp_matr_double(Matrix({sm_wrap(solveable)}), Matrix({{0.125, 7.625, 0., 16.25, -12.625}})));
}
