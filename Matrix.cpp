#include <iostream>
#include <cmath>

#include "Matrix.hpp"

Matrix::Matrix(matrix_t grid) :
	grid_(grid)
{}

Matrix::Matrix(matrix_t &grid) :
	grid_(grid)
{}

Matrix::Matrix(size_t x, size_t y, val_t value = 0) :
	grid_(y, std::vector <val_t> (x, value))
{}

Matrix::Matrix(size_t diagonal) :
	grid_(diagonal, std::vector <val_t> (diagonal, 0)) {
	for(int i = 0; i < Width(); ++i) {
		grid_[i][i] = 1;
	}
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

size_t	Matrix::Height() const {
	return grid_.size();
}

size_t	Matrix::Width() const {
	return grid_.front().size();
}

bool	Matrix::Square() const {
	return Height() == Width();
}

void	Matrix::MakeSquare() {
	if(!Square())
		throw std::runtime_error("Matrix::MakeSquare has made a slip.");

	long long diff = Height() - Width();
	if(!diff)
		return;
	if(diff < 0)
		for(size_t i = 0; i < Height(); ++i)
			grid_[i].resize(Height());
	if(diff > 0)
		grid_.resize(Width());
}

Matrix	Matrix::Join(const Matrix &B) const {
	const Matrix &A = *this;

	if(A.Height() != B.Height())
		throw std::runtime_error("Matrix::Join The matrixes have different heights");

	Matrix C(Height(), A.Width());
	for(size_t y = 0; y < Height(); ++y) {
		for(size_t x = 0; x < A.Width(); ++x)
			C[y][x] = A[y][x];
		for(size_t x = 0; x < B.Width(); ++x)
			C[y].push_back(B[y][x]);
	}
	std::cout << "\n\x1b[033;41m\x1b[033;1m\x1b[033;97m[     FLAG     ]\x1b[033;0m\n\n";
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
	Matrix C(B.Width(), Height(), 0);

	if(Width() != B.Height())
		throw std::runtime_error("Matrix::Operator* The matrixes have different dimensions");

	for(size_t i = 0; i < Height(); ++i)
		for(int j = 0; j < B.Width(); ++j) {
			C[i][j] = 0.0;
			for(int k = 0; k < Width(); ++k)
				C[i][j] += A[i][k] * B[k][j];
		}
	return C;
}

Matrix	Matrix::Transpose()						const {
	Matrix A(Height(), Width());
	for(size_t x = 0; x < Width(); ++x)
		for(size_t y = 0; y < Height(); ++y)
			A[x][y] = grid_[y][x];
	return A;
}

void	Matrix::Swap_Lines(const size_t line1, const size_t line2)	{
	std::swap(grid_[line1], grid_[line2]);
}

void	Matrix::Add_Line(const size_t line1, const size_t line2) {
	std::vector <val_t> line = grid_[line2];
	if(line.size() != Width())
		throw std::runtime_error("Matrix::Add_Line Improper size of a line passed..");
	for(size_t x = 0; x < Width(); ++x)
		grid_[line1][x] += line[x];
}

void	Matrix::Multiply_Line(const size_t line1, const val_t k) {
	if(!k)
		throw std::runtime_error("Matrix::Multiply_Line Can't multiply by 0.");
	for(size_t x = 0; x < Width(); ++x)
		grid_[line1][x] *= k;
}

void	Matrix::Swap_Columns(const size_t clm1, const size_t clm2)	{
	for(size_t y = 0; y < Height(); ++y) {
		val_t tmp = grid_[y][clm1];
		grid_[y][clm1] = grid_[y][clm2];
		grid_[y][clm2] = tmp;
	}
}

void	Matrix::Add_Column(const size_t clm1, const size_t clm2) {
	for(size_t y = 0; y < Height(); ++y)
		grid_[y][clm1] += grid_[y][clm2];
}

void	Matrix::Multiply_Column(const size_t clm1, const val_t k) {
	if(!k)
		throw std::runtime_error("Matrix::Multiply_Line Can't multiply by 0.");
	for(size_t y = 0; y < Height(); ++y)
		grid_[y][clm1] *= k;
}

Matrix	Matrix::GetInverse() const {
	Matrix	*common	= new Matrix(this->Join(Matrix(Height())));
	common->DoGauss();
	Matrix inverse = Matrix(common->SubMatrix(Width(), common->Width() - Width()));

	std::cout << "MATRIX:" << std::endl;
	for(size_t y = 0; y < inverse.Height(); ++y) {
		for(size_t x = 0; x < inverse.Width(); ++x)
			std::cout << float(inverse[y][x]) << "\t";
		std::cout << "\n\n";
	}

	delete common;
	return inverse;
}

void	Matrix::DoGauss() {
	bool *free = new bool[Height()];
	for(size_t i = 0; i < Height(); ++i)
		free[i] = true;
	for(size_t clm = 0; clm < Width(); ++clm)
		for(size_t ln = 0; ln < Height(); ++ln)
			if(grid_[ln][clm] && free[ln]) {
				free[ln] = false;
				for(size_t ln2 = 0; ln2 < Height(); ++ln2) {
					val_t k = (ln2 == ln) ?
						(grid_[ln2][clm] - 1) / grid_[ln2][clm]
								:
						(grid_[ln2][clm]) / grid_[ln][clm]
					;
//					for(size_t clm2 = 0; clm2 < Width(); ++clm2)
//						grid_[ln2][clm2] -= k * grid_[ln][clm2];
				}
				break;
			}
	delete(free);
}
