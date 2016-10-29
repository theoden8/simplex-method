#include "Vector.hpp"


Vector::scalar_t Vector::First() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.front();
}

Vector::scalar_t Vector::Last() const {
	ASSERT_DOMAIN(Size() > 0);
	return grid_.back();
}
