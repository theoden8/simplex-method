#include "Tensor.hpp"
#include "TensorTemplates.hpp"


temptensor(N)
Tensor <N> Tensor<N>::operator+() const {
	return *this;
}

temptensor(N)
Tensor <N> Tensor<N>::operator-() const {
	Tensor <N> T(*this);
	for(auto &it : grid_)
		it = -it;
	return T;
}


temptensor(N)
Tensor <N> Tensor<N>::operator+(const Tensor <N> &other) const {
	Tensor <N> T(*this);
	T += other;
	return T;
}

temptensor(N)
Tensor <N> Tensor<N>::operator-(const Tensor <N> &other) const {
	operator+(-other);
}

temptensor(N)
Tensor <N> Tensor<N>::operator*(const Tensor <0> &scalar) const {
	Tensor <N> T(*this);
	T *= scalar;
	return T;
}

temptensor(N)
Tensor <N> Tensor<N>::operator/(const Tensor <0> &scalar) const {
	Tensor <N> T(*this);
	T /= scalar;
	return T;
}


temptensor(N)
void Tensor<N>::operator+=(const Tensor <N> &other) {
	ASSERT_DOMAIN(Size() == other.Size());
	for(size_t i = 0; i < Size(); ++i)
		grid_[i] += other[i];
}

temptensor(N)
void Tensor<N>::operator-=(const Tensor <N> &other) {
	operator+=(-other);
}

temptensor(N)
void Tensor<N>::operator*=(const Tensor <0> &scalar) {
	for(size_t i = 0; i < Size(); ++i)
		grid_[i] *= scalar;
}

temptensor(N)
void Tensor<N>::operator/=(const Tensor <0> &scalar) {
	ASSERT_DOMAIN(scalar != 0.);
	operator*=(Tensor <0> (1.) / scalar);
}
