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
	grid_(y, row_t (x, value))
{
	Determinant();
}

Matrix::Matrix(size_t diagonal) :
	grid_(diagonal, row_t (diagonal, 0)) {
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

std::vector <Matrix::val_t> &Matrix::operator [] (size_t line) {
	return grid_[line];
}

const std::vector <Matrix::val_t> &Matrix::operator [] (size_t line) const {
	return grid_[line];
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

Matrix	Matrix::Concatenate_Lines(const Matrix &B) const {
	if(Width() != B.Width())
		throw std::runtime_error("Matrix::Concatenate_Lines The matrixes have different widths");
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
	Matrix C(B.Width(), A.Height(), 0);

	if(A.Height() != B.Height())
		throw std::runtime_error("Matrix::Operator* The matrixes have different dimensions");
	size_t depth = A.Height();

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

Matrix	Matrix::Swap_Lines(const size_t line1, const size_t line2) const {
	Matrix result = *this;
	std::swap(result[line1], result[line2]);
	return result;
}

Matrix	Matrix::Add_To_Line(const size_t line1, const size_t line2, const val_t k = 1) const {
	if(!k)		throw std::runtime_error("Matrix::Add_To_Line Can't multiply by 0.");
	Matrix result = *this;
	if(result[line2].size() != Width())
		throw std::runtime_error("Matrix::Add_To_Line Improper size of a line passed..");
	for(size_t x = 0; x < Width(); ++x)
		result[line2][x] += result[line1][x] * k;
	return result;
}

Matrix	Matrix::Multiply_Line(const size_t line1, const val_t k) const {
	if(k == 1)
		return *this;
	return Add_To_Line(line1, line1, k - 1);
}

Matrix	Matrix::Swap_Columns(const size_t clm1, const size_t clm2) const {
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		std::swap(result[y][clm1], result[y][clm2]);
	return result;
}

Matrix	Matrix::Add_To_Column(const size_t clm1, const size_t clm2, const val_t k = 1) const {
	if(!k)		throw std::runtime_error("Matrix::Add_To_Column Can't multiply by 0.");
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][clm2] += result[y][clm1] * k;
	return result;
}

Matrix	Matrix::Multiply_Column(const size_t clm1, const val_t k) const {
	if(k == 1)
		return *this;
	return Add_To_Column(clm1, clm1, k - 1);
}

Matrix	Matrix::Invert() const {
	Matrix	common	= this->Concatenate_Columns(Matrix(Height())).Gauss();
	Matrix inverse = Matrix(common.SubMatrix(Width(), common.Width() - Width()));

	std::cout << "MATRIX:" << std::endl;
	for(size_t y = 0; y < inverse.Height(); ++y) {
		for(size_t x = 0; x < inverse.Width(); ++x)
			std::cout << float(inverse[y][x]) << "\t";
		std::cout << "\n\n";
	}

	return inverse;
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
				result = result.Multiply_Line(ln, 1/result[ln][clm]);
				for(size_t ln2 = 0; ln2 < Height(); ++ln2)
					if(result[ln2][clm] && ln != ln2)
						result = result.Add_To_Line(ln, ln2, -result[ln2][clm] / result[ln][clm]);
				break;
			}
	delete(free);
	return result;
}

Matrix	Matrix::GetOptimizedMinimum(row_t C) const {
	if(C.size() != Width() - 1)
		throw std::runtime_error("Matrix::GetOptimizedMinimum can't accept vector of inappropriate size.");
	C.insert(C.begin(), 0);
	Print(Matrix({C}), "To minimize:");
	Matrix A(*this);
	for(size_t y = 0; y < Height(); ++y) {
		A[y].insert(A[y].begin(), A[y].back());
		A[y].pop_back();
		if(A[y].front() < 0)
			A = A.Multiply_Line(y, -1);
	}
	Print(A, "Left side");
	Matrix Diag = Matrix(Height(), 1, 0).Concatenate_Lines(Matrix(Height()));
	Matrix M = Matrix({C}).Concatenate_Lines(A).Concatenate_Columns(Matrix(Diag));
	Print(M, "Whole M matrix");
	for(size_t x = 1; x < Width(); ++x) {
		for(size_t y1 = 1; y1 < M.Height(); ++y1) {
			Print(M, std::string("\033[0;4;96mLooking at").c_str(), x, y1);
			std::cin.get(); std::cout << "\033c";
			if(!M[y1][x] || M[0][x] <= 0)
				continue;
			bool suitable = 1;
			for(size_t y2 = 1; y2 < M.Height(); ++y2) {
				if(y1 == y2)
					continue;
				if(M[y2][0] - M[y1][0] * (M[y2][x] / M[y1][x]) >= 0) {
					suitable = 0;
					break;
				}
			}
			if(!suitable)
				continue;
			M = M.Multiply_Line(y1, 1. / M[y1][x]);
			for(size_t y2 = 0; y2 < M.Height(); ++y2)
				if(M[y2][x] && y2 != y1)
					M = M.Add_To_Line(y1, y2, -M[y2][x] / M[y1][x]);
		}
	}
	Print(M, "Finished optimizing");
	return M;
}

void	Matrix::Print(const Matrix &A, const char *NAME, const size_t h_x, const size_t h_y) {
	const size_t SPACING = 35;
	std::cout << "\033[1;40;93m  [ Printing another matrix ] \033[0m\033[1;40;35m-><-\t# " << NAME << ":\033[0m" << std::endl;
	for(size_t y = 0; y < A.Height(); ++y) {
		std::cout << '\t';
		for(size_t x = 0; x < A.Width(); ++x) {
			std::string number = std::to_string(A[y][x]);
			if(h_x == x && h_y == y)
				number = std::string() + "\033[103;30m" + number + " \033[0m";
			else if(number[0] == '-')
				number = std::string() + "\033[1;40;91m" + number + "\033[0m";
			else if(A[y][x] == 0)
				number = std::string() + "\033[1;40;92m" + number + "\033[0m";
			else
				number = std::string() + "\033[1;40;97m" + number + "\033[0m";
//			std::string number = std::to_string(.1 * long(A[y][x] * 10));
//			number.erase(number.find_last_not_of('0') + 1, std::string::npos);
//			if(number[number.length() - 1] == '.')
//				number = number.substr(0, number.length() - 1);
			std::cout << number << std::string(std::max(SPACING - number.length(), size_t(1)), ' ');
		}
		std::cout << std::endl;
	}
}
