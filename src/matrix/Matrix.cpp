#include <cmath>

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Matrix.hpp"

Matrix::Matrix(const matrix_t &grid) :
	grid_(grid)
{}

Matrix::Matrix(const size_t x, const size_t y, const real_t value) :
	grid_(y, Vector(x, value))
{}

Matrix::Matrix(const size_t diagonal) :
	grid_(diagonal, Vector(diagonal, 0))
{
	for(int i = 0; i < Width(); ++i)
		grid_[i][i] = 1;
}

const Matrix::matrix_t *Matrix::GetGrid() const {
	return &grid_;
}

const bool Matrix::operator== (const Matrix &other) const {
	if(Width() == other.Width() && Height() == other.Height())
		for(size_t y = 0; y < Height(); ++y)
			for(size_t x = 0; x < Width(); ++x)
				if(grid_[y][x] != other[y][x])
					return false;
	return true;
}

Vector &Matrix::operator [] (const size_t row) {
	return grid_[row];
}

const Vector &Matrix::operator [] (const size_t row) const {
	return grid_[row];
}

const size_t Matrix::Height() const {
	return grid_.size();
}

const size_t Matrix::Width() const {
	if(!Height())
		return 0;
	return grid_.front().Size();
}

const bool Matrix::Square() const {
	return Height() == Width();
}

void Matrix::Print(const Matrix &M, const char *NAME, const size_t h_x, const size_t h_y) {
	const size_t SPACING = 30;
	const static real_t precision = 0.0000001;
	std::cout << "\033[1;40;93m  [ Printing another matrix ] \033[0m\033[1;40;35m-><-\t# " << NAME << ":\033[0m" << std::endl;
	for(size_t y = 0; y < M.Height(); ++y) {
		std::cout << '\t';
		for(size_t x = 0; x < M.Width(); ++x) {
			bool is_zero = std::abs(M[y][x]) <= precision;
			std::string number = "\033[";
			if(h_x == x && h_y == y)
				number += "103;30";
			else if(!is_zero && M[y][x] < 0)
				number += "1;40;91";
			else if(is_zero)
				number += "1;40;92";
			else
				number += "1;40;97";
			number += "m" + (is_zero ? std::to_string(real_t(0)) : std::to_string(M[y][x])) + " \033[0m";
			std::cout << number << std::string(std::max(SPACING - number.length(), (size_t)1), ' ');
		}
		std::cout << std::endl;
	}
}
