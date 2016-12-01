#include "Vector.hpp"


Vector::Vector(size_t size, scalar_t value) :
	Tensor <scalar_t> (size, value)
{}

Vector::Vector(line_t grid) :
	Tensor <scalar_t> (grid)
{}

Vector::Vector(size_t size, const std::function <scalar_t (size_t)> &construct) :
	Tensor <scalar_t> (size)
{
	for(size_t i = 0; i < grid_.size(); ++i)
		grid_[i] = construct(i);
}


Vector::~Vector()
{}


const bool Vector::operator== (const Vector &other) const {
	if(Size() != other.Size())
		return false;

	for(size_t i = 0; i < Size(); ++i)
		if(grid_[i] != other[i])
			return false;
	return true;
}


void Vector::Print(const Vector &v) {
	static const int CELL = 15;
	for(const auto &it : v.grid_) {
		size_t len = printf("%Lf" , scalar_t(it));
		for(size_t i = 0; i < CELL - len; ++i)
			putchar(' ');
	}
	putchar('\n');
}
