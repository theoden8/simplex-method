#include <Vector.hpp>
#include "Matrix.hpp"


const bool Matrix::Square() const {
	return Height() == Width();
}

const size_t Matrix::Height() const {
	return Size();
}

const size_t Matrix::Width() const {
	if(!Height())
		return 0;
	return grid_.front().Size();
}
