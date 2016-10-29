#include "Matrix.hpp"

Vector::scalar_t Matrix::Trace() const {
	ASSERT_DOMAIN(Square());

	real_t sum = 0;
	for(size_t i = 0; i < Height(); ++i)
		sum += grid_[i][i];

	return sum;
}

Vector::scalar_t Matrix::Det() const {
	ASSERT_DOMAIN(Square());

	try {
		std::pair <Matrix, Matrix> LU = LUDecomposition(*this);
		real_t det = 1;
		for(const auto &m : {LU.first, LU.second}) {
			for(size_t d = 0; d < m.Width(); ++d)
				det *= m[d][d];
		}
		return det;
	} catch(real_t exception) {
		return 0.;
	}
}
