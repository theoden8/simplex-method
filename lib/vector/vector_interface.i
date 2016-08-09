%module smvector

%inline %{
	#include <thread>
	#include <functional>
	#include <vector>
	#include "Vector.hpp"
	typedef long double real_t;
	typedef std::vector <real_t> line_t;
%}

%include "std_vector.i"
%include typemaps.i

%apply real_t &OUTPUT { real_t & fA  };

namespace std {
	%template(vector_real) vector <real_t>;
}

%include "Vector.hpp"
