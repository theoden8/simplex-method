#include "Vector.hpp"


const Vector::line_t &Vector::GetLine() const {
	return line_;
}


size_t Vector::Size() const {
	return line_.size();
}

real_t Vector::First() const {
	ASSERT_DOMAIN(Size() > 0);
	return line_.front();
}

real_t Vector::Last() const {
	ASSERT_DOMAIN(Size() > 0);
	return line_.back();
}


real_t &Vector::operator[] (const size_t index) {
	return line_[index];
}

const real_t &Vector::operator[] (const size_t index) const {
	return line_[index];
}
