#include "Tensor.hpp"

#define temptensor(var) template <size_t var>

temptensor(N)
Tensor<N>::Tensor(size_t size):
	grid_(size)
{}

temptensor(N)
Tensor<N>::Tensor(size_t size, Tensor <N - 1> value):
	grid_(size, value)
{}

temptensor(N)
Tensor<N>::Tensor(tensor_t grid):
	grid_(grid)
{}

temptensor(N)
Tensor<N>::~Tensor()
{}


temptensor(N)
size_t Tensor<N>::Size() const {
	return grid_.size();
}

temptensor(N)
const Tensor<N>::Tensor::tensor_t &Tensor<N>::GetGrid() const {
	return grid_;
}


temptensor(N)
void Tensor<N>::Pop() {
	grid_.pop_back();
}

temptensor(N)
void Tensor<N>::Push(const subtensor_t value) {
	grid_.push_back(value);
}

temptensor(N)
void Tensor<N>::Push(const Tensor <N> &other) {
	grid_.insert(grid_.end(), other.grid_.begin(), other.grid_.end());
}

temptensor(N)
void Tensor<N>::Resize(const size_t new_size, const subtensor_t value) {
	return Tensor<N>(Size(), [&](const size_t idx) {return grid_[Size() - idx - 1];});
}


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
