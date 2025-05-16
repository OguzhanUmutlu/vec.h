# 📦 `vec.h` - Lightweight Dynamic Arrays in C

`vec.h` is a **header-only**, lightweight, macro-based dynamic array (vector) implementation for C. It makes working
with resizable arrays as easy and intuitive as possible — without needing to manage memory manually every time.

### ✅ Features

* Simple to integrate: just include a single header file
* Customizable for any data type
* Auto-resizing
* Basic vector operations: push, pop, resize, clear, free, etc.
* Optional printing, contains method and memory freeing hooks

---

## 🔧 Getting Started

### 1. **Include the header**

```c
#include "vec.h"
```

### 2. **Define a vector type**

To create a dynamic array of `int`, do:

```c
vec_define(int, VecInt, int_vec);
```

This creates a vector type called `VecInt` with functions prefixed with `int_vec`.

---

## 🚀 Usage Example

```c
#include <stdio.h>
#include "vec.h"

// Defines the vector type VecInt that contains int elements
// int_vec determines the function prefix
vec_define(int, VecInt, int_vec);

int main() {
    VecInt v;
    int_vec_init(&v);  // Initialize the vector

    // Add elements
    int_vec_push(&v, 10);
    int_vec_push(&v, 20);
    int_vec_push(&v, 30);

    // Print elements
    for (int i = 0; i < v.size; i++) {
        printf("v[%d] = %d\n", i, v.data[i]);
    }

    // Access an element
    printf("Element at index 1: %d\n", int_vec_at(v, 1));

    // Modify an element
    int_vec_set(&v, 1, 200);
    printf("Modified element at index 1: %d\n", int_vec_at(v, 1));

    // Remove last element
    int popped = int_vec_pop(&v);
    printf("Popped: %d\n", popped);

    // Clean up
    free(v.data);
    return 0;
}
```

---

## 🧪 Output

```
v[0] = 10
v[1] = 20
v[2] = 30
Element at index 1: 20
Modified element at index 1: 200
Popped: 30
```

## 🛠️ Technical Overview of All Functions

Below is a full list of available vector functions. These are generated using:

```c
vec_define(type, VectorName, NAME)
```

Once defined, you can call functions like `vec_init_NAME`, `vec_push_NAME`, etc.

---

### 🔧 Initialization & Allocation

| Function                       | Description                                   | Example                         |
| ------------------------------ | --------------------------------------------- | ------------------------------- |
| `vec_alloc_NAME()`             | Allocates a vector on the heap.               | `VecInt *v = vec_alloc_NAME();` |
| `vec_init_NAME(&v)`            | Initializes vector with default capacity (4). | `vec_init_NAME(&v);`            |
| `vec_init2_NAME(&v, capacity)` | Initializes vector with specific capacity.    | `vec_init2_NAME(&v, 16);`       |

---

### 📦 Data Manipulation

| Function                         | Description                                   | Example                         |
| -------------------------------- | --------------------------------------------- | ------------------------------- |
| `vec_push_NAME(&v, value)`       | Adds an element to the end.                   | `vec_push_NAME(&v, 42);`        |
| `vec_pop_NAME(&v)`               | Removes and returns the last element.         | `int x = vec_pop_NAME(&v);`     |
| `vec_back_NAME(v)`               | Gets a pointer to the last element.           | `int *last = vec_back_NAME(v);` |
| `vec_at_NAME(v, index)`          | Gets a value at an index (with bounds check). | `int x = vec_at_NAME(v, 2);`    |
| `vec_set_NAME(&v, index, value)` | Sets the value at a given index.              | `vec_set_NAME(&v, 1, 99);`      |

---

### 🧹 Management

| Function                                       | Description                                               | Example                                  |
| ---------------------------------------------- | --------------------------------------------------------- | ---------------------------------------- |
| `vec_clear_NAME(&v)`                           | Clears the vector (sets size to 0).                       | `vec_clear_NAME(&v);`                    |
| `vec_empty_NAME(v)`                            | Checks if vector is empty. Returns 1 or 0.                | `if (vec_empty_NAME(v)) { /* empty */ }` |
| `vec_reverse_NAME(&v)`                         | Reverses the vector.                                      | `vec_reverse_NAME(&v);`                  |
| `vec_resize_NAME(&v, new_size, default_value)` | Resizes the vector, filling new slots with default value. | `vec_resize_NAME(&v, 10, 0);`            |
| `vec_shrink_NAME(&v)`                          | Shrinks capacity to match size.                           | `vec_shrink_NAME(&v);`                   |
| `vec_reserve_NAME(&v, capacity)`               | Ensures vector can hold at least `capacity` elements.     | `vec_reserve_NAME(&v, 100);`             |
| `vec_realloc_NAME(&v, capacity)`               | Reallocates to a new capacity (use with caution).         | `vec_realloc_NAME(&v, 50);`              |

---

### Changing the function name convention

The function name format can be simply changed by defining `__vec_fn_name_format` macro before including the library:

```c
#define __vec_fn_name_format(name, base, fn_name) hello_##base##_fn_name
#include "vec.h" // has to be after the macro
```

In the macro:

* `name`: The name of the vector like `VecInt`
* `base`: The name of the function like `push`
* `fn_name`: The third argument when defining the vector like `int_vec`

---

### 🧩 Optional: Contains method

To define a contains method for your vector type:

```c
vec_define_contains(int, VecInt, vec_contains_VecInt)
```

Then use it:

```c
int_vec_contains(v, 42); // returns 1 if 42 is in the vector
```

You can also define a custom comparison function, useful in structs:

```c
int my_compare(int a, int b) {
    return a == b; // or any other comparison logic
}
```

Then use it to define your contains method:

```c
vec_define_contains_fn(int, VecInt, vec_contains_VecInt, my_compare)
```

---

### 🖨️ Optional: Printing (if you define `vec_define_print`)

To define a print function for debugging:

```c
vec_define_print(int, VecInt, vec_print_NAME, my_int_print)
```

Then implement:

```c
void my_int_print(int x, int indent) {
    printf("%d", x);
}
```

Use like:

```c
vec_print_NAME(v, 1);
```

---

### 🧼 Optional: Freeing Items (e.g. struct with malloc inside)

For complex types:

```c
vec_define_free(MyStruct, VecStruct, vec_free_NAME, vec_struct_free)
```

And define:

```c
void vec_struct_free(VecStruct s) {
    // this will be called for each element in the vector
    free(s.ptr); // or whatever cleanup is needed
}
```

Then call:

```c
// if you are using a stack-allocated vector use:
vec_free_NAME(&v);

// if you have used the _alloc() feature to allocate the vector in the heap use this(will also free itself):
vec_free_NAME_heap(v);
```

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](./LICENSE) file for details.

---

## 💬 Feedback & Contributions

Found a bug? Have an improvement idea? Feel free to open an issue or submit a pull request.

> ⚠️ This library is intentionally minimal — you’re encouraged to adapt and extend it for your specific use cases.

---

📁 **Looking for the previous version?**
The legacy implementation has been preserved in [`README_legacy.md`](./README_legacy.md) and [
`vec_legacy.h`](./vec_legacy.h) for reference.
