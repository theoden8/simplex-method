#pragma once

#include <type_traits>

#define temptensor(subtype) template <class subtype>
#define temptensor_a(subtype, argtype) temptensor(subtype) template <class argtype>
#define temptensor_as(subtype, argtype, scalar) temptensor(subtype) template <class argtype, class scalar>
#define temptensor_tr(subtype, rettype) temptensor(subtype) template <class rettype>
#define temptensor_tras(subtype, rettype, argtype, scalar) temptensor(subtype) template <class rettype, class argtype, class scalar>
#define temptensor_tra(subtype, rettype, argtype) temptensor(subtype) template <class rettype, class argtype>
#define temptensor_a(subtype, argtype) temptensor(subtype) template <class argtype>
