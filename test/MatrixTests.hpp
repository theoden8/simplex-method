#include "Matrix.hpp"
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MatrixTest : public ::testing::Test {
protected:
	MatrixTest() {}
	virtual ~MatrixTest() {}
	virtual void SetUp() {}
	virtual void TearDown() {
		std::cout << "\n---------------------TEAR DOWN-------------------\n" << std::endl;
	}
};
