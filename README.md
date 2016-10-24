## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides three static libraries: tensor, vector and matrix (all tested) with various algorithms. The aim of this project was to implement simplex method, but because on the way of understanding how to implement it I created a Matrix class with useful operations algorithms, it was convenient to elaborate a little bit on linear algebra in C++ and to implement vectors, LUDecomposition, Determinant and more.

## Bugs/Errors

Method `GaussianElimination` is not yet properly tested (causes termination in some cases) and `SimplexMethod` is only verified by hand.

## Compilation

To compile the program, use:

    cmake .
    make

## Testing

To test the program, use:

    make test
    ./_simplex ./test/tests/... ; echo $? # some file

The supporting programs for generating examples are **matrix_gen**, **vector_gen**, they generate samples from given dimensions.

## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
