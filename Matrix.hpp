#pragma once

#include <vector>
#include <stack>
#include <cstdio>

class Matrix {
public:
	typedef long double val_t;
	typedef std::vector <std::vector <val_t> > matrix_t;
	typedef std::vector <val_t> row_t;
	val_t det;
private:
	matrix_t grid_;
public:
	Matrix		(matrix_t grid);
	Matrix		(matrix_t &grid);
	Matrix		(size_t x, size_t y, val_t value);
	Matrix		(size_t diagonal);
	matrix_t GetGrid();
	std::vector <val_t>		&operator[]	(size_t line);
	const std::vector <val_t>	&operator[]	(size_t line)			const;
private:
	void	Determinant	();
	size_t	Width		()							const;
	size_t	Height		()							const;
	bool	Square		()							const;
	Matrix	MakeSquare	()							const;
	Matrix	Concatenate	(const Matrix &B)					const;
	Matrix	SubMatrix	(const size_t start, const size_t length)		const;
public:
	Matrix	operator*	(const Matrix &B)					const;
	Matrix	Transpose	()							const;
	Matrix	Swap_Lines	(const size_t line1, const size_t line2)		const;
	Matrix	Add_To_Line	(const size_t line1, const size_t line2, const val_t k)	const;
	Matrix	Multiply_Line	(const size_t line1, const val_t k)			const;
	Matrix	Swap_Columns	(const size_t clm1, const size_t clm2)			const;
	Matrix	Add_To_Column	(const size_t clm1, const size_t clm2, const val_t k)	const;
	Matrix	Multiply_Column	(const size_t clm1, const val_t k)			const;
	Matrix	Invert		()							const;
	Matrix	Gauss		()							const;
};
