#include "Vector.hpp"


Vector Vector::Reverse() const {
	return Vector(Size(), [&](const size_t idx) {return grid_[Size() - idx - 1];});
}
