## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides three static libraries: tensor, vector and matrix (all tested) with various algorithms. The aim of this project was to implement simplex method at first, but then it expanded as a collection of linear algebra libraries.

## Bugs/Errors

* `Matrix::GaussianElimination` is not yet properly tested (causes termination in some cases).
* `Matrix::SimplexMethod` is only verified by hand.

## Compilation

To compile the program, use:

	./compile

## Testing

To test the program, use:

    make test
    ./_simplex ./test/tests/... ; echo $? # some file

The supporting programs for generating examples are **matrix_gen**, **vector_gen**, they generate samples from given dimensions.

## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
