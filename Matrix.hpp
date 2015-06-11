#pragma once

#include <vector>

class Matrix {
public:
	typedef		long double		val_t;
	typedef		std::vector <val_t>	row_t;
	typedef		std::vector <row_t>	matrix_t;
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
	row_t		&operator[]	(size_t line);
	const row_t	&operator[]	(size_t line)					const;
	size_t	Width		()							const;
	size_t	Height		()							const;
private:
	void	Determinant	();
	bool	Square		()							const;
	Matrix	MakeSquare	()							const;
	Matrix	Concatenate_Columns	(const Matrix &B)				const;
	Matrix	Concatenate_Lines	(const Matrix &B)				const;
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
//	row_t	GetOptimizedMinimum	(row_t C)					const;
	Matrix	GetOptimizedMinimum	(row_t C)					const;
	static void	Print		(const Matrix &A, const char *NAME = "", const size_t h_x = -1, const size_t h_y = -1);
};
