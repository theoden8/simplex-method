#pragma once

#include <vector>

class Matrix {
public:
	typedef		long double		val_t;
	typedef		std::vector <val_t>	line_t;
	typedef		std::vector <line_t>	matrix_t;
private:
	val_t det_;
	matrix_t grid_;
public:
	Matrix		(matrix_t grid);
	Matrix		(matrix_t &grid);
	Matrix		(size_t x, size_t y, val_t value);
	Matrix		(size_t diagonal);
	matrix_t	GetGrid()							const;
	bool		operator==	(const Matrix &other)				const;
	line_t		&operator[]	(size_t row);
	const line_t	&operator[]	(size_t row)					const;
	size_t	Width		()							const;
	size_t	Height		()							const;
private:
	void	Determinant	();
	bool	Square		()							const;
	Matrix	MakeSquare	()							const;
	Matrix	Concatenate_Columns	(const Matrix &B)				const;
	Matrix	Concatenate_Rows	(const Matrix &B)				const;
	Matrix	SubMatrix	(const size_t start, const size_t length)		const;
public:
	Matrix	operator*	(const Matrix &B)					const;
	Matrix	Transpose	()							const;
	Matrix	Swap_Rows	(const size_t row1, const size_t row2)		const;
	Matrix	Add_To_Row	(const size_t row1, const size_t row2, const val_t k)	const;
	Matrix	Multiply_Row	(const size_t row1, const val_t k)			const;
	Matrix	Swap_Columns	(const size_t clm1, const size_t clm2)			const;
	Matrix	Add_To_Column	(const size_t clm1, const size_t clm2, const val_t k)	const;
	Matrix	Multiply_Column	(const size_t clm1, const val_t k)			const;
	Matrix	Invert		()							const;
	Matrix	Gauss		()							const;
//	line_t	GetOptimizedMinimum	(line_t C)					const;
	Matrix	GetOptimizedMinimum	(line_t C)					const;
	static void	Print		(const Matrix &A, const char *NAME = "", const size_t h_x = -1, const size_t h_y = -1);
};
