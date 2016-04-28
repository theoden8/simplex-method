# TODO

* ## Project structure

	* `lib/<library; test/` >> `lib/<library>/src`, `lib/<library>/test`
	* Change CMakeFiles.
		* Variable names `PROJECT_TEST` `PROJECT_LIB`

* ## Source

	* ### Vector

		* real_t Vector::operator^
			* scalar multiplication/dot product
		* real_t Vector::abs
	
		* #### further
		
			* real_t Vector::operator*
				* vector multiplication. requires matrix interface for calculation
			* Vector::Functional
				* fix the Map function and use against loops.
				* create the Reduce function and use against sums/products.
			* Vector::Permutations
				* shuffle using a number
				* get current combinatorical permutation using compare function
				* will require `gmp`

	* ### Matrix

		* Matrix::operator*	
			* change a loop into scalar multiplication.
		* Matrix::SimplexMethod
			* create a wrapper for canoncial form.
		* Matrix::GaussianElimination
			* prevent termination in case something goes wrong.
		* Matrix::Minor

		* #### further

			* Exceptions
				These need better system.
			* Matrix::Rank

* ## Then

	git checkout master
	git merge vectors