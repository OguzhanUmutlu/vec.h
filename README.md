# vec.h - A Header-Only Vector Library in C

`vec.h` is a lightweight, header-only C library that implements a dynamic array (vector) with basic functionalities like resizing, pushing, popping, and indexing, all wrapped up in simple macros. It's a useful utility for managing dynamic arrays with minimal overhead and maximum performance. This implementation is ideal for any C project that requires flexible, resizable containers, similar to `std::vector` in C++.

## Features

* **Dynamic Resizing**: The vector automatically resizes when more capacity is required.
* **Push and Pop**: Easily add elements to the back of the vector and remove the last element.
* **Element Access**: Provides convenient access with bounds checking and custom error handling.
* **Memory Management**: Handles memory allocation and deallocation, ensuring no memory leaks.
* **Capacity Control**: You can manually reserve capacity or shrink the vector to fit its size.

## Functions & Macros

* `vec(type)` - Defines a vector type of a given element `type`.
* `vec_init(type, v, reserved)` - Initializes a vector with a specified reserved capacity.
* `vec_create(type, reserved)` - Creates a vector and initializes it with a reserved capacity.
* `vec_push(type, v, x)` - Adds an element `x` to the end of the vector.
* `vec_pop(v)` - Removes the last element from the vector.
* `vec_back(v)` - Accesses the last element in the vector.
* `vec_clear(v)` - Clears all elements in the vector.
* `vec_empty(v)` - Returns whether the vector is empty.
* `vec_at(v, i)` - Accesses an element at index `i` with bounds checking.
* `vec_resize(type, v, n, def_val)` - Resizes the vector to hold `n` elements, filling with `def_val` if needed.
* `vec_shrink(type, v)` - Shrinks the vector's capacity to fit its size.
* `vec_reserve(type, v, n)` - Reserves at least `n` elements' worth of capacity.
* `vec_print(type, fn, v, indent)` - Prints the vector contents using a custom print function for each element.
* `vec_free(v)` - Frees the memory used by the vector.
* `vec_free2(v, fn)` - Frees the memory and applies a custom function `fn` to free each element.

## Example Usage

```c
#include "vec.h"
#include <stdio.h>

void print_number(int x, int indent) {
    for (int i = 0; i < indent; i++) putchar(' ');
    printf("%d", x);
}

int main() {
    // Create a vector of integers with initial capacity of 4
    vec(int) v;
    vec_init(int, v, 4);

    // Push some values into the vector
    vec_push(int, v, 10);
    vec_push(int, v, 20);
    vec_push(int, v, 30);
    vec_push(int, v, 40);

    // Print the vector with a custom function
    vec_print(int, print_number, v, 0);

    // Access an element by index
    printf("\nElement at index 2: %d\n", vec_at(v, 2));

    // Pop an element
    printf("Popped: %d\n", vec_pop(v));

    // Clear the vector
    vec_clear(v);

    // Free the vector's memory
    vec_free(v);
    return 0;
}
```

### Output:

```
[10, 20, 30, 40]
Element at index 2: 30
Popped: 40
```

## Compilation

Since `vec.h` is a header-only library, there's no need to link against any compiled library. Simply include it in your project, and you're good to go!

To compile the example code:

```bash
gcc -o example example.c
./example
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to fork this repository and submit pull requests. Contributions are welcome!
