#pragma once

#include <vector>
#include <cassert>

#include <lztree.hpp>

class Matrix {
	using vec_t = std::vector<float>;
	using mat_t = std::vector<vec_t>;
	mat_t mat;
public:
	explicit Matrix(size_t h, size_t w):
		mat(mat_t(h, vec_t(w)))
	{
		for(size_t i = 0; i < h; ++i)
			for(size_t j = 0; j < w; ++j)
				mat[i][j] = (i == j);
	}

	size_t height() const {
		return mat.size();
	}

	size_t width() const {
		if(height() == 0)
			return 0;
		return mat.front().size();
	}

	Matrix operator*(float scalar) {
		Matrix res(height(), width());
		for(size_t i = 0; i < height(); ++i)
			for(size_t j = 0; j < width(); ++j)
				res.mat[i][j] = mat[i][j] * scalar;
		return res;
	}

	Matrix operator*(const Matrix &other) {
		Matrix res(height(), other.width());
		assert(width() == other.height());
		for(size_t i = 0; i < height(); ++i) {
			for(size_t j = 0; j < other.width(); ++j) {
				float sum = 0.;
				for(size_t k = 0; k < width(); ++k)
					sum += mat[i][k] * other.mat[k][j];
				res.mat[i][j] = sum;
			}
		}
		return res;
	}
	friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
		for(size_t i = 0; i < m.height(); ++i) {
			for(size_t j = 0; j < m.width(); ++j)
				os << m.mat[i][j] << " ";
			os << std::endl;
		}
		return os;
	}
};
