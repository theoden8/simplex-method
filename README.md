## Author

Created by Kirill Rodriguez on 08/2015.

## Program

This program provides an interface to standard matrix operations and algorithms, which include row/column operations, transposition, inversion, multiplication, gaussian elimination and, in particular, simplex method (using the standard form).

Method `GaussianElimination` is not yet properly tested; `Determinant` gives incorrect result because `LUPDecomposition` outputs some random stuff.

## Usage

To compile the program, use:

    cmake .
    make

Followed by:

    # temporarily unsupported:
    ./_matrix ./src/tests/... ; echo $? # some file

The supporting program for generating examples is **matrix_gen.pl**, which prints matrices of given width and height.

## Testing

To run google-tests, execute:

    ./_testmatrix


## References

* Papadimitriou, C.H. and Steiglitz, K., 1982. Combinatorial optimization: Algorithms and Complexity. Courier Corporation.
