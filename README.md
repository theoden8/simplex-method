## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides an interface to standard matrix operations and algorithms, which include row/column operations, transposition, inversion, multiplication, gaussian elimination and, in particular, simplex method (using the standard form).

Methods `GaussianElimination` and `Invert` are not tested due to absence of `Determinant` function. Simplex method examples are only fully verified by hand.

## Usage

To compile the program, use:

    cmake .
    make

Followed by:

    ./_matrix ./src/tests/... ; echo $? # some file

The supporting program for generating examples is **matrix_gen.pl**, which prints matrices of given width and height.

## Testing

To run google-tests, execute:

    ./_testmatrix


## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
