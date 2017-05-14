#include "LZEvalTests.hpp"
#include "matrix.hpp"

TEST_F(LZEvalTest, IntsTest) {
	auto tree = -make_mul(make_add(5, 6), 16) * 5;
	std::cout << tree << std::endl;
	std::cout << tree() << std::endl;
}

TEST_F(LZEvalTest, NumTest) {
	auto tree = make_neg(make_add(2, 3) + make_sub(5, 6) * make_add(3, 0)) / 3; // = -4
	std::cout << tree << std::endl;
	std::cout << tree() << std::endl;
}

TEST_F(LZEvalTest, BifFuncTest) {
	static const auto &func = [](auto a, auto b, auto c) { return a + b * c; };
	static const auto &make_func = [](auto a, auto b, auto c) {
		return Operator<decltype(func), decltype(a), decltype(b), decltype(c)>(func, a, b, c);
	};
	auto tree = make_func(4, 5, 6);
	std::cout << tree() << std::endl;
}

TEST_F(LZEvalTest, BifFuncMatTest) {
	static const auto &func = [](auto a, auto b, auto c) { return a * b * c; };
	static const auto &make_func = [](auto a, auto b, auto c) {
		return Operator<decltype(func), decltype(a), decltype(b), decltype(c)>(func, a, b, c);
	};
	float f = 10.;
	Matrix a(10, 10), b(10, 10);
	auto tree = make_func(a, b * 4, f);
	std::cout << tree() << std::endl;
}

TEST_F(LZEvalTest, MatTest) {
	Matrix m(10, 10), n(10, 10);
	auto mattree = make_mul(n, 3) * m;
	std::cout << mattree << std::endl;
	std::cout << "operator is recursive: " << is_recursive<Operator<decltype(add), float, Matrix> >::value << std::endl;
	std::cout << "matrix is recursive: " << is_recursive<Matrix>::value << std::endl;
	std::cout << "float is recursive: " << is_recursive<float>::value << std::endl;
	std::cout << "mattree is recursive: " << is_recursive<decltype(mattree)>::value << std::endl;
	/* mattree.printrec(); */
	std::cout << mattree() << std::endl;
}
