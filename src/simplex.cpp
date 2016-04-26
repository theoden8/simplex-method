#include <cassert>
#include <cstdlib>
#include <iostream>

typedef unsigned long size_t;

#ifdef VERBOSE
#warning Verbosity level is defined.
#endif

#include <tuple>
#include <Matrix.hpp>

// a bunch of methods to help with testing simplex method
static char verify_solution_validity(const Matrix&, const Vector&, const Vector&);

#include <fstream>
char run_test(const char *filename) {
	std::fstream file;
	file.open(filename, std::fstream::in);
	size_t width, height;
	file >> width >> height;
	if(!width || !height)
		return 1;
	Matrix::matrix_t values(height, Vector(width, 0.));
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			file >> values[i][j];
	Vector optimized(width - 1, 0.);
	for(int i = 0; i < width - 1; ++i)
		file >> optimized[i];
	Matrix A(values);
	try {
		const static Vector solution(Matrix::SimplexMethod(A, *optimized.GetLine()));
		#ifndef VERBOSE
		for(size_t i = 0; i < solution.Size(); ++i)
			std::cout << solution[i] << " ";
		std::cout << std::endl;
		#endif
		return verify_solution_validity(A, solution, optimized);
	} catch(std::exception &e) {
		return 1;
	}
	file.close();
}

#include <cmath>
static char verify_solution_validity(const Matrix &A, const Vector &solution, const Vector &optimized) {
	// Substitute values into all rows and verify equations
	const static real_t PRECISION = 0.001;
	for(int i = 0; i < solution.Size() - 1; ++i)
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

int main(const int argc, const char **argv) {
	assert(argc <= 2);
	return run_test(argv[1]);
}
