#pragma once

#include <tuple>

template <class ... Ts>
class Evaluation {
public:
	typedef typename std::tuple <Ts...> ::type F;
protected:
	std::tuple <Ts...> fields;
public:
	Evaluation(Ts... elems);
	virtual ~Evaluation();
	virtual operator F() = 0;
};
