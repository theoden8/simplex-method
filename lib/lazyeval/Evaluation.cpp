#include "Evaluation.hpp"

template <class... Ts>
Evaluation<Ts...>::Evaluation(Ts... elems):
	fields(std::make_tuple(elems...))
{}

template <class... Ts>
Evaluation<Ts...>::~Evaluation()
{}
