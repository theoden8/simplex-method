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
	size_t i = 0;
	for(auto &x : *this)
		x = construct(i++);
}


Vector::~Vector()
{}


void Vector::Print(const Vector &v) {
	static const int CELL = 15;
	for(const auto &it : v) {
		size_t len = printf("%Lf" , scalar_t(it));
		for(size_t i = 0; i < CELL - len; ++i)
			putchar(' ');
	}
	putchar('\n');
}
