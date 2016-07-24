#include "Vector.hpp"

void Vector::Push(const real_t value) {
	line_.push_back(value);
}

void Vector::Push(const Vector &other) {
	line_.insert(line_.end(), other.GetLine().begin(), other.GetLine().end());
}

void Vector::Pop() {
	line_.pop_back();
}

void Vector::Resize(const size_t new_size, const real_t value = real_t(0)) {
	line_.resize(new_size, value);
}

Vector Vector::Reverse() const {
	return Vector(Size(), [&](const size_t idx) {return line_[Size() - idx - 1];});
}
