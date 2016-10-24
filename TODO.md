# TODO

* ## Project structure

	* `lib/<library; lib/<library>/test/` >> `lib/<library>/src`, `lib/<library>/test`
	* Separate matrix and vector definitions from their algorithms.

* ## Source

	* ### Vector

		* real_t Vector::operator*
			* vector multiplication. requires matrix interface for calculation
		* Vector::Functional
			* fix Reduce function and use against sums/products
		* Vector::Permutations
			* shuffle using a number
			* get current combinatorical permutation using compare function
			* will require bignum interface

	* ### Matrix

		* Matrix::SimplexMethod
			* create a wrapper for canoncial form.
		* Matrix::GaussianElimination
			* prevent termination in case something goes wrong.
		* Matrix::Minor
		* Exceptions
			* These need better system than the existing one.
		* Matrix::Rank
	
	* ### Tensor
	
		* Inherit to Vector and Matrix to reduce code duplication.
	
	* ### Lazy Evaluation
	
		* Replace return values with function wrapper classes with implicit conversion to the intended return value, thus building lazy evaluation tree.