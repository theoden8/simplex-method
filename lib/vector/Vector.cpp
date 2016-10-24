#include "Vector.hpp"

Vector::Vector():
	line_()
{}

Vector::Vector(size_t size, real_t value) :
	line_(size, value)
{}

Vector::Vector(line_t line) :
	line_(line)
{}

Vector::Vector(size_t size, const std::function <real_t (size_t)> &construct) :
	line_(size)
{
	for(size_t i = 0; i < line_.size(); ++i)
		line_[i] = construct(i);
}


Vector::~Vector() {
}


const bool Vector::operator== (const Vector &other) const {
	if(Size() != other.Size())
		return false;

	for(size_t i = 0; i < Size(); ++i)
		if(line_[i] != other[i])
			return false;
	return true;
}


void Vector::Print(const Vector &v) {
	static const int CELL = 15;
	for(const auto &it : v.GetLine()) {
		size_t len = printf("%Lf" , it);
		for(size_t i = 0; i < CELL - len; ++i)
			putchar(' ');
	}
	putchar('\n');
}
