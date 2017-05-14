#include "Vector.hpp"


Vector::scalar_t Vector::First() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.front();
}

Vector::scalar_t Vector::Last() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.back();
}

Vector Vector::operator=(Tensor <scalar_t> &t) {
	return static_cast<Vector>(t);
}

Vector Vector::operator=(Tensor <scalar_t> t) {
	return static_cast<Vector>(t);
}
