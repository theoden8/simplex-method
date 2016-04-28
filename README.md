## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides an interface to standard matrix operations and algorithms, which include row/column operations, transposition, inversion, multiplication (and so on) and, in particular, simplex method (using the standard form).

Method `GaussianElimination` is not yet properly tested and `SimplexMethod` is only validated by hand.

## Compilation

To compile the program, use:

    cmake .
    make

## Testing

To test the program, use:

    make test
    ./_simplex ./test/tests/... ; echo $? # some file

The supporting program for generating examples is **matrix_gen.pl**, which prints matrices of given width and height.

## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
