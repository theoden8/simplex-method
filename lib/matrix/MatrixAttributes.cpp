#include <Vector.hpp>
#include "Matrix.hpp"


const Matrix::matrix_t &Matrix::GetGrid() const {
	return grid_;
}


const bool Matrix::Square() const {
	return Height() == Width();
}

const size_t Matrix::Height() const {
	return grid_.size();
}

const size_t Matrix::Width() const {
	if(!Height())
		return 0;
	return grid_.front().Size();
}


Vector &Matrix::operator [] (const size_t row) {
	return grid_[row];
}

const Vector &Matrix::operator [] (const size_t row) const {
	return grid_[row];
}
