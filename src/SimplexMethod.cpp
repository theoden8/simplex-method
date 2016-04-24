#include "Matrix.hpp"

Matrix::line_t Matrix::SimplexMethod(Matrix A, line_t C) {
	if(C.size() != A.Width() - 1)
		throw std::runtime_error("Matrix::SimplexMethod Can not use vector of inappropriate width.");
	C.insert(C.begin(), 0);
	_MATRIX_VERBOSE_SELFPRINT(Matrix({C}), "To minimize:");
	std::vector <size_t> match(A.Height());
	std::vector <bool> in_basis(A.Width() - 1, 0);
	for(size_t y = 0; y < A.Height(); ++y) {
		A[y].insert(A[y].begin(), A[y].back());
		A[y].pop_back();
		if(A[y].front() < 0)
			A = A.MultiplyRow(y, -1);
		match[y] = y + A.Width();
	}
//	Print(A, "Left side");
	Matrix M =
		Matrix({C})
		.ConcatenateRows(A)
		.ConcatenateColumns(Matrix(A.Height(), 1, 0)
		.ConcatenateRows(Matrix(A.Height())));
	_MATRIX_VERBOSE_SELFPRINT(M.SubMatrix(0, A.Width()), "Initial M matrix");
	size_t x = 0;
	bool optimizing;
	int slack_count = A.Height();
	do {
		optimizing = 0;
		for(size_t x = 1; x < A.Width(); ++x) {
			if (
						slack_count
					&&
						in_basis[x - 1]
				||
						!slack_count
					&&
						M[0][x] <= 0
			) continue;
			val_t theta = 0;
			size_t chosen_y = 0;
			for(size_t another_y = 1; another_y < M.Height(); ++another_y) {
				if(M[another_y][x] <= 0)
					continue;
				val_t next_theta = M[another_y][0] / M[another_y][x];
				if(!chosen_y || theta > next_theta) {
					theta = next_theta;
					chosen_y = another_y;
				}
			}
			if(!chosen_y)
				continue;
			#if VERBOSE < 3
			_MATRIX_VERBOSE_SELFPRINT(M.SubMatrix(0, A.Width()), "\033[0;4;96mLooking at", x, chosen_y);
			#else
			_MATRIX_VERBOSE_SELFPRINT(M, "\033[0;4;96mLooking at", x, chosen_y);
			std::cout << std::endl;
			_MATRIX_VERBOSE_LOG(in_basis, "\t\t\t", '\t', std::endl);
			_MATRIX_VERBOSE_LOG(match, "\t\t\t", '\t', std::endl);
			std::cout << "\t\t\t" << slack_count << std::endl;
			#endif
			_MATRIX_VERBOSE_WAITENTER;
			M = M.MultiplyRow(chosen_y, 1. / M[chosen_y][x]);
			for(size_t another_y = 0; another_y < M.Height(); ++another_y) {
				if(chosen_y != another_y)
					M = M.AddToRow(chosen_y, another_y, -M[another_y][x]);
			}
			if(match[chosen_y - 1] >= A.Width()) {
				slack_count -= (slack_count > 0);
				if(!slack_count) {
					_MATRIX_VERBOSE_SELFPRINT(M, "Found positive solutions");
					match[chosen_y - 1] = x;
					break;
				}
			}
			if(slack_count && x == A.Width() - 1) {
				int to_add = 0;
				for(size_t y = 1; y < A.Height(); ++y)
					to_add += !M[y][0];
				/* std::cout << "\t\t\t\033[1;96m" << to_add << "\033[0m" << std::endl; */
				if(slack_count <= to_add)
					slack_count = 0;
				else {
					_MATRIX_VERBOSE_SELFPRINT(M, "Exceptional matrix:");
					throw std::runtime_error("Matrix::SimplexMethod The system has no solutions in non-negative values.");
				}
			}
			match[chosen_y - 1] = x;
			in_basis[x - 1] = 1;
			optimizing = 1;
		}
	} while(optimizing);
	_MATRIX_VERBOSE_SELFPRINT(M, "Finished optimizing");
	/* _MATRIX_VERBOSE_SELFPRINT(Matrix({C})); */
	line_t solution(A.Width(), 0);
	/* _MATRIX_VERBOSE_LOG(match, "", ' ', std::endl); */
	solution[A.Width() - 1] = M[0][0];
	for(int i = 0; i < A.Height(); ++i)
		solution[match[i] - 1] = M[i + 1][0];
	_MATRIX_VERBOSE_SELFPRINT(Matrix({solution}), "Solution");
	return solution;
}