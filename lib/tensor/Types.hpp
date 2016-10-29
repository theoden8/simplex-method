#pragma once

#include <stdexcept>
#include <vector>

typedef unsigned long size_t;
typedef long double real_t;

template <size_t DIM>
struct tensor_t {
	typedef std::vector <typename tensor_t <DIM - 1> :: type > type;
};

template <>
struct tensor_t <0> {
	typedef real_t type;
};

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CODE_LOCATION "\033[1m" __FILE__ "\033[0m::\033[93m" TOSTRING(__LINE__) "\033[0m"
#define CONDITION_TOSTR(CONDITION) " ( \033[1;4m" STRINGIFY(CONDITION) "\033[0m )"

#define ASSERT_DOMAIN(CONDITION) { \
	if(!(CONDITION)) { \
		throw std::domain_error("\033[1;91mdomain_error\033[0m" CODE_LOCATION CONDITION_TOSTR(CONDITION));\
	} \
}
