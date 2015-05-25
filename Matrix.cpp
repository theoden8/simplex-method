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
	bool *B = new bool(Width() * Height());
	det = Determinant(0, 1e9, B, 0);
	std::cout << det << std::endl;
	delete B;
}

Matrix::val_t	Matrix::Determinant(val_t value, val_t last, bool *scan, bool inverse) const {
	for(size_t i = 0; i < Width() * Height(); ++i) {
		val_t elem = grid_[i / Height()][i % Width()];
		if(scan[i])
			continue;
		scan[i] = true;
		inverse = (inverse == last < elem);
		value += (-2 * inverse + 1) * Determinant(value, elem, scan, inverse);
		scan[i] = false;
	}
	return value;
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

void	Matrix::Transpose()						{
	Matrix A(Height(), Width());
	for(size_t x = 0; x < Width(); ++x)
		for(size_t y = 0; y < Height(); ++y)
			A[x][y] = grid_[y][x];
	*this = A;
}

void	Matrix::Swap_Lines(const size_t line1, const size_t line2)	{
	std::swap(grid_[line1], grid_[line2]);
}

void	Matrix::Add_To_Line(const size_t line1, const size_t line2, const val_t k = 1) {
	if(!k)
		throw std::runtime_error("Matrix::Add_To_Line Can't multiply by 0.");
	std::vector <val_t> line = grid_[line2];
	if(line.size() != Width())
		throw std::runtime_error("Matrix::Add_To_Line Improper size of a line passed..");
	for(size_t x = 0; x < Width(); ++x)
		grid_[line1][x] += line[x] * k;
}

void	Matrix::Multiply_Line(const size_t line1, const val_t k) {
	Add_To_Column(line1, line1, k - 1);
}

void	Matrix::Swap_Columns(const size_t clm1, const size_t clm2)	{
	for(size_t y = 0; y < Height(); ++y) {
		val_t tmp = grid_[y][clm1];
		grid_[y][clm1] = grid_[y][clm2];
		grid_[y][clm2] = tmp;
	}
}

void	Matrix::Add_To_Column(const size_t clm1, const size_t clm2, const val_t k = 1) {
	if(!k)
		throw std::runtime_error("Matrix::Add_To_Column Can't multiply by 0.");
	for(size_t y = 0; y < Height(); ++y)
		grid_[y][clm1] += grid_[y][clm2] * k;
}

void	Matrix::Multiply_Column(const size_t clm1, const val_t k) {
	Add_To_Column(clm1, clm1, k - 1);
}

Matrix	Matrix::Inverse() const {
	Matrix	common	= this->Join(Matrix(Height()));
	common.DoGauss();
	Matrix inverse = Matrix(common.SubMatrix(Width(), common.Width() - Width()));

	std::cout << "MATRIX:" << std::endl;
	for(size_t y = 0; y < inverse.Height(); ++y) {
		for(size_t x = 0; x < inverse.Width(); ++x)
			std::cout << float(inverse[y][x]) << "\t";
		std::cout << "\n\n";
	}

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
					val_t k = (ln2 == ln) ?  (grid_[ln2][clm] - 1) / grid_[ln2][clm] : (grid_[ln2][clm]) / grid_[ln][clm] ;
					if(k) Add_To_Line(ln2, ln, -k);
				}
				break;
			}
	delete(free);
}
