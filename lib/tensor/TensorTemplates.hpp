#pragma once

#define temptensor(subtype) template <class subtype>
#define temptensor_s(subtype, scalar) temptensor(subtype) template <typename scalar>
#define temptensor_tr(subtype, rettype) temptensor(subtype) template <class rettype>
#define temptensor_trs(subtype, rettype, scalar) temptensor(subtype) template <class rettype, typename scalar>
#define temptensor_tra(subtype, rettype, argtype) temptensor(subtype) template <class rettype, class argtype>
#define temptensor_a(subtype, argtype) temptensor(subtype) template <class argtype>
