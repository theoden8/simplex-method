#include "Matrix.hpp"

Matrix::val_t Matrix::Trace() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Trace need a square matrix.");
	}

	val_t sum = 0;
	for (size_t i = 0; i < Height(); ++i)
		sum += grid_[i][i];

	return sum;
}
