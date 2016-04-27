#include "Matrix.hpp"

// matching chosen_y if 0 or with the biggest positive relation column[0]/column[i]
static real_t ChooseBestRow(const Matrix &M, const size_t x) {
	real_t theta(0);
	size_t chosen_y = 0;
	for(size_t another_y = 1; another_y < M.Height(); ++another_y) {
		if(M[another_y][x] <= real_t(0)) {
			continue;
		}

		real_t next_theta = M[another_y][0] / M[another_y][x];
		if(chosen_y == 0 || theta > next_theta) {
			theta = next_theta;
			chosen_y = another_y;
		}
	}
	return chosen_y;
}

// subtract the chosen row from all others using column x
static void EliminateChosenRow(Matrix &M, const size_t row, const size_t x) {
	M = M.MultiplyRow(row, 1. / M[row][x]);
	for(size_t y = 0; y < M.Height(); ++y) {
		if(row == y) {
			continue;
		}
		M = M.AddToRow(row, y, -M[y][x]);
	}
}

Vector Matrix::SimplexMethod(Matrix A, Vector::line_t C) {
	if(C.size() != A.Width() - 1)
		throw std::runtime_error("Matrix::SimplexMethod Can not use vector of inappropriate width.");
	C.insert(C.begin(), real_t(0));
	_MATRIX_VERBOSE_SELFPRINT(Matrix({C}), "To minimize:");
	std::vector <size_t> match(A.Height()); // matches the row with the solution (column)
	std::vector <bool> in_basis(A.Width() - 1, 0); // records if a solution is in bases
	for(size_t y = 0; y < A.Height(); ++y) {
		real_t last = A[y].Last();
		A[y].Pop();
		Vector A2 = Vector(1, last);
		A2.Push(A[y]);
		A[y] = A2;
		if(A[y].First() < 0)
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
	int slack_count = A.Height(); // number of slack variables in match

	do {
		optimizing = false;
		for(size_t x = 1; x < A.Width(); ++x) {
			if(
						slack_count
					&&
						in_basis[x - 1]
				||
						!slack_count
					&&
						M[0][x] <= 0
			)
			{
				continue;
			}
			const size_t chosen_y = ChooseBestRow(M, x);
			if(chosen_y == 0)
				continue;

			//verbose
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
			//verbose

			EliminateChosenRow(M, chosen_y, x);

			if(match[chosen_y - 1] >= A.Width()) {
				slack_count -= (slack_count > 0);
				if(slack_count == 0) {
					_MATRIX_VERBOSE_SELFPRINT(M, "Found positive solutions");
					match[chosen_y - 1] = x;
					break;
				}
			}

			if(slack_count != 0 && x == A.Width() - 1) {
				int to_add = 0;
				for(size_t y = 1; y < A.Height(); ++y) {
					to_add += (M[y][0] == real_t(0));
				}
				/* std::cout << "\t\t\t\033[1;96m" << to_add << "\033[0m" << std::endl; */
				if(slack_count <= to_add) {
					slack_count = 0;
				} else {
					_MATRIX_VERBOSE_SELFPRINT(M, "Exception occured:");
					throw std::runtime_error("Matrix::SimplexMethod The system has no solutions in non-negative values.");
				}
			}

			match[chosen_y - 1] = x;
			in_basis[x - 1] = true;
			optimizing = true;
		}
	} while(optimizing);
	_MATRIX_VERBOSE_SELFPRINT(M, "Finished optimizing");
	/* _MATRIX_VERBOSE_SELFPRINT(Matrix({C})); */
	Vector solution(A.Width(), 0);
	/* _MATRIX_VERBOSE_LOG(match, "", ' ', std::endl); */
	solution[A.Width() - 1] = M[0][0];
	for(size_t i = 0; i < A.Height(); ++i) {
		solution[match[i] - 1] = M[i + 1][0];
	}
	_MATRIX_VERBOSE_SELFPRINT(Matrix({solution}), "Solution");
	return solution;
}
