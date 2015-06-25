#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <string>

#include "Matrix.hpp"

Matrix::Matrix(matrix_t grid) :
	grid_(grid)
{
	Determinant();
}

Matrix::Matrix(matrix_t &grid) :
	grid_(grid)
{
	Determinant();
}

Matrix::Matrix(size_t x, size_t y, val_t value = 0) :
	grid_(y, line_t (x, value))
{
	Determinant();
}

Matrix::Matrix(size_t diagonal) :
	grid_(diagonal, line_t (diagonal, 0)) {
	for(int i = 0; i < Width(); ++i)
		grid_[i][i] = 1;
	Determinant();
}

Matrix::matrix_t Matrix::GetGrid() const {
	return grid_;
}

bool	Matrix::operator== (const Matrix &other) const {
	if(Width() == other.Width() && Height() == other.Height())
		for(size_t y = 0; y < Height(); ++y)
			for(size_t x = 0; x < Width(); ++x)
				if(grid_[y][x] != other[y][x])
					return false;
	return true;
}

Matrix::line_t	&Matrix::operator [] (size_t row) {
	return grid_[row];
}

const Matrix::line_t	&Matrix::operator [] (size_t row) const {
	return grid_[row];
}

size_t	Matrix::Height() const {
	return grid_.size();
}

size_t	Matrix::Width() const {
	return grid_.front().size();
}

void	Matrix::Determinant() {
	return;
}

bool	Matrix::Square() const {
	return Height() == Width();
}

Matrix	Matrix::MakeSquare() const {
	Matrix result = *this;
	long long diff = Height() - Width();
	if(!diff)
		return result;
	if(diff < 0)
		for(size_t i = 0; i < Height(); ++i)
			result[i].resize(Height());
	if(diff > 0)
		result.grid_.resize(Width());
	return result;
}

Matrix	Matrix::Concatenate_Columns(const Matrix &B) const {
	if(Height() != B.Height())
		throw std::runtime_error("Matrix::Concatenate_Columns The matrixes have different heights");
	Matrix A = *this;
	for(size_t y = 0; y < Height(); ++y)
		A[y].insert(A[y].end(), B[y].begin(), B[y].end());
	return A;
}

Matrix	Matrix::Concatenate_Rows(const Matrix &B) const {
	if(Width() != B.Width())
		throw std::runtime_error("Matrix::Concatenate_Rows The matrixes have different widths");
	Matrix A = *this;
	A.grid_.insert(A.grid_.end(), B.grid_.begin(), B.grid_.end());
	return A;
}

Matrix	Matrix::SubMatrix(const size_t start, const size_t length) const {
	if(start + length > Width())
		throw std::runtime_error("Matrix::SubMatrix Out of width.");

	Matrix A(matrix_t(Height(), {}));
	for(size_t y = 0; y < Height(); ++y)
		for(size_t x = 0; x < length; ++x)
			A[y].push_back(grid_[y][start + x]);
	return A;
}

Matrix	Matrix::operator* (const Matrix &B) const {
	const Matrix &A = *this;
	if(A.Height() != B.Height())
		throw std::runtime_error("Matrix::Operator* The matrixes have different dimensions");
	Matrix C(B.Width(), A.Height(), 0);
	const size_t depth = A.Height();
	for(size_t y1 = 0; y1 < A.Height(); ++y1)
		for(size_t x2 = 0; x2 < B.Width(); ++x2)
			for(size_t i = 0; i < depth; ++i)
				C[y1][x2] += A[y1][i] * B[i][x2];
	return C;
}

Matrix	Matrix::Transpose() const {
	Matrix result(Height(), Width());
	for(size_t x = 0; x < Width(); ++x)
		for(size_t y = 0; y < Height(); ++y)
			result[x][y] = grid_[y][x];
	return result;
}

Matrix	Matrix::Swap_Rows(const size_t row1, const size_t row2) const {
	Matrix result = *this;
	std::swap(result[row1], result[row2]);
	return result;
}

Matrix	Matrix::Add_To_Row(const size_t row1, const size_t row2, const val_t k = 1) const {
	Matrix result = *this;
	if(result[row2].size() != Width())
		throw std::runtime_error("Matrix::Add_To_Row Improper size of a row passed..");
	for(size_t x = 0; x < Width(); ++x)
		result[row2][x] += result[row1][x] * k;
	return result;
}

Matrix	Matrix::Multiply_Row(const size_t row1, const val_t k) const {
	if(!k)	throw std::runtime_error("Matrix::Multiply_Row Can't multiply by 0.");
	if(k == 1)
		return *this;
	return Add_To_Row(row1, row1, k - 1);
}

Matrix	Matrix::Swap_Columns(const size_t clm1, const size_t clm2) const {
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		std::swap(result[y][clm1], result[y][clm2]);
	return result;
}

Matrix	Matrix::Add_To_Column(const size_t clm1, const size_t clm2, const val_t k = 1) const {
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][clm2] += result[y][clm1] * k;
	return result;
}

Matrix	Matrix::Multiply_Column(const size_t clm1, const val_t k) const {
	if(!k)	throw std::runtime_error("Matrix::Multiply_Column Can't multiply by 0.");
	if(k == 1)
		return *this;
	return Add_To_Column(clm1, clm1, k - 1);
}

Matrix	Matrix::Invert() const {
	Matrix	common	= this->Concatenate_Columns(Matrix(Height())).Gauss();
	return	Matrix(common.SubMatrix(Width(), common.Width() - Width()));
}

Matrix	Matrix::Gauss()	const {
	Print(*this, "Gaussing");
	Matrix result = *this;
	bool *free = new bool[Height()];
	for(size_t i = 0; i < Height(); ++i)
		free[i] = true;
	for(size_t clm = 0; clm < Width(); ++clm)
		for(size_t ln = 0; ln < Height(); ++ln)
			if(result[ln][clm] && free[ln]) {
				free[ln] = false;
				result = result.Multiply_Row(ln, 1/result[ln][clm]);
				for(size_t ln2 = 0; ln2 < Height(); ++ln2)
					if(result[ln2][clm] && ln != ln2)
						result = result.Add_To_Row(ln, ln2, -result[ln2][clm] / result[ln][clm]);
				break;
			}
	delete(free);
	return result;
}

Matrix::line_t	Matrix::GetOptimizedMinimum(line_t C) const {
	if(C.size() != Width() - 1)
		throw std::runtime_error("Matrix::GetOptimizedMinimum can't accept vector of inappropriate size.");
	C.insert(C.begin(), 0);
//	Print(Matrix({C}), "To minimize:");
	Matrix A(*this);
	std::vector <size_t>	match	(Height());
	std::vector <bool>	in_basis	(Width() - 1, 0);
	for(size_t y = 0; y < Height(); ++y) {
		A[y].insert(A[y].begin(), A[y].back());
		A[y].pop_back();
		if(A[y].front() < 0)
			A = A.Multiply_Row(y, -1);
		match[y] = y + Width();
	}
//	Print(A, "Left side");
	Matrix M =
		Matrix({C})
		.Concatenate_Rows(A)
		.Concatenate_Columns(Matrix(Height(), 1, 0)
		.Concatenate_Rows(Matrix(Height())));
	Print(M.SubMatrix(0, Width()), "Initial M matrix");
	size_t x	= 0;
	bool optimizing;
	int slack_count	= Height();
	do {
		optimizing = 0;
		for(size_t x = 1; x < Width(); ++x) {
			if (
						slack_count
					&&
						in_basis[x - 1]
				||
						!slack_count
					&&
						M[0][x] <= 0
			) continue;
			val_t	theta	= 0;
			size_t chosen_y	= 0;
			for(size_t another_y = 1; another_y < M.Height(); ++another_y) {
				if(M[another_y][x] <= 0)
					continue;
				val_t next_theta = M[another_y][0] / M[another_y][x];
				if(!chosen_y || theta > next_theta) {
					theta		= next_theta;
					chosen_y	= another_y;
				}
			}
			if(!chosen_y)
				continue;
			Print(M.SubMatrix(0, Width()), std::string("\033[0;4;96mLooking at").c_str(), x, chosen_y);
			std::cout << "\n\t\t\t";
			for(auto each : in_basis)
				std::cout << each << '\t';
			std::cout << "\n\t\t\t";
			for(auto &each : match)
				std::cout << each << '\t';
			std::cout << "\n\t\t\t" << slack_count << "\nPress enter to continue.";
			std::cin.get(); std::cout << "\033c";
			M = M.Multiply_Row(chosen_y, 1. / M[chosen_y][x]);
			for(size_t another_y = 0; another_y < M.Height(); ++another_y)
				if(chosen_y != another_y)
					M = M.Add_To_Row(chosen_y, another_y, -M[another_y][x]);
			if(match[chosen_y - 1] >= Width()) {
				slack_count -= (slack_count > 0);
				if(!slack_count) {
					Print(M.SubMatrix(0, Width()), "Found positive solutions");
					break;
				}
			}
			if(slack_count && x == Width() - 1) {
				int to_add = 0;
				for(size_t y = 1; y < Height(); ++y)
					to_add += !M[y][0];
				std::cout << "\t\t\t\033[1;96m" << to_add << "\033[0m" << std::endl;
				if(slack_count <= to_add)
					slack_count = 0;
				else {
					Print(M.SubMatrix(0, Width()), "Exceptional matrix:");
					throw std::runtime_error("Matrix::GetOptimizedMinimum The system has no solutions in non-negative values.");
				}
			}
			match[chosen_y - 1]	= x;
			in_basis[x - 1]		= 1;
			optimizing		= 1;
		}
	} while(optimizing);
	Print(M.SubMatrix(0, Width()), "Finished optimizing");
	Print(Matrix({C}));
	line_t solution(Width());
	for(size_t i = 1; i < Width(); ++i)
		solution[i - 1] = M[0][i];
	solution[Width() - 1] = M[0][0];
	return solution;
}

void	Matrix::Print(const Matrix &M, const char *NAME, const size_t h_x, const size_t h_y) {
	const size_t SPACING = 45;
	std::cout << "\033[1;40;93m  [ Printing another matrix ] \033[0m\033[1;40;35m-><-\t# " << NAME << ":\033[0m" << std::endl;
	val_t precision = 0.0000009;
	for(size_t y = 0; y < M.Height(); ++y) {
		std::cout << '\t';
		for(size_t x = 0; x < M.Width(); ++x) {
			std::string number = (std::abs(M[y][x]) > precision) ? std::to_string(M[y][x]) : std::to_string(val_t(0));
			if(h_x == x && h_y == y)
				number = std::string() + "\033[103;30m" + number + " \033[0m";
			else if(number[0] == '-')
				number = std::string() + "\033[1;40;91m" + number + "\033[0m";
			else if(std::abs(M[y][x]) < precision)
				number = std::string() + "\033[1;40;92m" + number + "\033[0m";
			else
				number = std::string() + "\033[1;40;97m" + number + "\033[0m";
			std::cout << number << std::string(std::max(SPACING - number.length(), size_t(1)), ' ');
		}
		std::cout << std::endl;
	}
}
