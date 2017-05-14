#pragma once

#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <class T>
struct is_recursive {
private:
	typedef char yes;
	typedef short no;
	template <typename C> static yes test(decltype(C::RECURSE_ME)*);
	template <typename C> static no test(...);
public:
	static constexpr const bool value = (sizeof(test<T>(0)) == sizeof(yes));
};

template <typename T, bool rec = is_recursive<T>::value> struct evaluate;
template <class T> struct evaluate <T, true> { static auto calc(const T &value) { return value(); } };
template <class T> struct evaluate <T, false> { static auto calc(const T &value) { return value; } };

template <typename F, typename ... As> class Operator;

namespace lz {
	namespace fn {
		static const auto &sgn_plus = [](auto a) { return +a; };
		static const auto &sgn_minus = [](auto a) { return -a; };
		static const auto &add = [](auto a, auto b) {return a + b; };
		static const auto &sub = [](auto a, auto b) {return a - b; };
		static const auto &mul = [](auto a, auto b) {return a * b; };
		static const auto &frac = [](auto a, auto b) {return a / b; };
	}
}

using namespace lz::fn;

// unary
static const auto &make_unary = [](auto &f, auto a) { return Operator<decltype(f), decltype(a)>(f, a); };
static const auto &make_pos = [](auto a) { return make_unary(sgn_plus, a); };
static const auto &make_neg = [](auto a) { return make_unary(sgn_minus, a); };

// binary
static const auto &make_binop = [](auto &f, auto a, auto b) { return Operator<decltype(f), decltype(a), decltype(b)>(f, a, b); };
static const auto &make_add = [](auto a, auto b) { return make_binop(add, a, b); };
static const auto &make_sub = [](auto a, auto b) { return make_binop(sub, a, b); };
static const auto &make_mul = [](auto a, auto b) { return make_binop(mul, a, b); };
static const auto &make_div = [](auto a, auto b) { return make_binop(frac, a, b); };

template <typename F, typename ... As>
class Operator {
protected:
	std::tuple <As...> args;
	static constexpr auto args_size = std::tuple_size<decltype(args)>::value;
	F func;
	typedef Operator<F, As...> THIS_T;
public:
	static const bool RECURSE_ME;

	Operator(F &func, As&... args):
		func(func),
		args(std::make_tuple(args...))
	{}

	virtual ~Operator()
	{}
private:
	template <typename T>
	decltype (auto) eval_node(const T &value) const {
		return evaluate<T>::calc(value);
	}

	template <size_t ... Idx>
	decltype(auto) eval_children(std::index_sequence<Idx...>) const {
		return func(eval_node(std::get<Idx>(args))...);
	}
public:
	decltype(auto) operator() () const {
		return eval_children(std::make_index_sequence<args_size>());
	}

	constexpr decltype(auto) operator-() const { return make_neg(*this); }
	constexpr decltype(auto) operator+() const { return make_pos(*this); }
	template <class R> constexpr decltype(auto) operator+(const R &other) { return make_add(*this, other); }
	template <class R> constexpr decltype(auto) operator-(const R &other) { return make_sub(*this, other); }
	template <class R> constexpr decltype(auto) operator*(const R &other) { return make_mul(*this, other); }
	template <class R> constexpr decltype(auto) operator/(const R &other) { return make_div(*this, other); }
private:
	template <size_t start, size_t end> struct oper_ostream {
		static void call(std::ostream &os, const THIS_T &op) {
			os << std::get<start>(op.args) << ", ";
			oper_ostream<start + 1, end>::call(os, op);
		}
	};
	template <size_t idx> struct oper_ostream <idx, idx> {
		static void call(std::ostream &os, const THIS_T &op) {
			os << std::get<idx>(op.args);
		}
	};
public:
	friend std::ostream &operator<<(std::ostream &os, THIS_T op) {
		os << "{";
		oper_ostream<0, args_size - 1>::call(os, op);
		os << "}";
		return os;
	}
};
