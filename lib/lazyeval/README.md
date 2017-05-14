# lztree

![picture](./_Icon.png)

## Author

Created by Kirill Rodriguez in 12/2016.

## Description

Small template library for lazy evaluations.

## Purpose

This is intended to be used with matrices, tensors, scalars and everything that can be added to anything else.

## Built with

* c++14
* make

## Features

* Trees with operations of positive arity
* Infers the types in compile-time
* Evaluates the tree

## License

The project is [licensed](./LICENSE) under MIT License.

## Usage

### Compilation flags

* `-std=c++1y` to enable c++14 standard

### Example

	#include <lztree.hpp>

	int main() {
		auto tree = -make_mul(make_add(5, 6), 16) * 5;
		std::cout << tree << std::endl;
		std::cout << tree() << std::endl;
	}

---

	output:
	{{{{5, 6}, 16}}, 5}
	-880
