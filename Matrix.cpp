#include <iostream>
#include <cmath>

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
	grid_(y, std::vector <val_t> (x, value))
{
	Determinant();
}

Matrix::Matrix(size_t diagonal) :
	grid_(diagonal, std::vector <val_t> (diagonal, 0)) {
	for(int i = 0; i < Width(); ++i) {
		grid_[i][i] = 1;
	}
	Determinant();
}

Matrix::matrix_t Matrix::GetGrid() {
	return grid_;
}

std::vector <Matrix::val_t> &Matrix::operator [] (size_t line) {
	return grid_[line];
}

const std::vector <Matrix::val_t> &Matrix::operator [] (size_t line) const {
	return grid_[line];
}

void	Matrix::Determinant() {
	return;
}

size_t	Matrix::Height() const {
	return grid_.size();
}

size_t	Matrix::Width() const {
	return grid_.front().size();
}

bool	Matrix::Square() const {
	return Height() == Width();
}

Matrix	Matrix::MakeSquare() const {
	if(!Square())
		throw std::runtime_error("Matrix::MakeSquare has made a slip.");
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

Matrix	Matrix::Concatenate(const Matrix &B) const {
	const Matrix &A = *this;

	if(A.Height() != B.Height())
		throw std::runtime_error("Matrix::Concatenate The matrixes have different heights");

	Matrix C(Height(), A.Width());
	for(size_t y = 0; y < Height(); ++y) {
		for(size_t x = 0; x < A.Width(); ++x)
			C[y][x] = A[y][x];
		for(size_t x = 0; x < B.Width(); ++x)
			C[y].push_back(B[y][x]);
	}
	return C;
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
	if(!k)
		throw std::runtime_error("Matrix::Add_To_Line Can't multiply by 0.");
	Matrix result = *this;
	std::vector <val_t> line = result[line2];
	if(line.size() != Width())
		throw std::runtime_error("Matrix::Add_To_Line Improper size of a line passed..");
	for(size_t x = 0; x < Width(); ++x)
		result[line1][x] += line[x] * k;
	return result;
}

Matrix	Matrix::Multiply_Line(const size_t line1, const val_t k) const {
	return Add_To_Column(line1, line1, k - 1);
}

Matrix	Matrix::Swap_Columns(const size_t clm1, const size_t clm2) const {
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y) {
		val_t tmp = result[y][clm1];
		result[y][clm1] = result[y][clm2];
		result[y][clm2] = tmp;
	}
	return result;
}

Matrix	Matrix::Add_To_Column(const size_t clm1, const size_t clm2, const val_t k = 1) const {
	if(!k)
		throw std::runtime_error("Matrix::Add_To_Column Can't multiply by 0.");
	Matrix result = *this;
	for(size_t y = 0; y < Height(); ++y)
		result[y][clm1] += result[y][clm2] * k;
	return result;
}

Matrix	Matrix::Multiply_Column(const size_t clm1, const val_t k) const {
	return Add_To_Column(clm1, clm1, k - 1);
}

Matrix	Matrix::Invert() const {
	Matrix	common	= this->Concatenate(Matrix(Height())).Gauss();
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
	Matrix result = *this;
	bool *free = new bool[Height()];
	for(size_t i = 0; i < Height(); ++i)
		free[i] = true;
	for(size_t clm = 0; clm < Width(); ++clm)
		for(size_t ln = 0; ln < Height(); ++ln)
			if(result[ln][clm] && free[ln]) {
				free[ln] = false;
				for(size_t ln2 = 0; ln2 < Height(); ++ln2) {
					val_t k = (ln2 == ln) ?  (result[ln2][clm] - 1) / result[ln2][clm] : (result[ln2][clm]) / result[ln][clm] ;
					if(k) Add_To_Line(ln2, ln, -k);
				}
				break;
			}
	delete(free);
	return result;
}
