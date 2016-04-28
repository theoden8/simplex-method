## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides an interface to standard matrix operations and algorithms, which include row/column operations, transposition, inversion, multiplication (and so on) and, in particular, simplex method (using the standard form). Apart from that the program provides extensive interface to vectors: scalar multiplication, constructors with lambdas and more.

## Inconsistencies

Method `GaussianElimination` is not yet properly tested and `SimplexMethod` is only validated by hand.

## Compilation

To compile the program, use:

    cmake .
    make

## Testing

To test the program, use:

    make test
    ./_simplex ./test/tests/... ; echo $? # some file

The supporting programs for generating examples are **matrix_gen**, **vector_gen** , generate samples from given dimensions.

## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
