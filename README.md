# 📦 `vec.h` - Lightweight Dynamic Arrays in C

`vec.h` is a **header-only**, lightweight, macro-based dynamic array (vector) implementation for C. It makes working
with resizable arrays as easy and intuitive as possible — without needing to manage memory manually every time.

### ✅ Features

* Simple to integrate: just include a single header file
* Customizable for any data type
* Auto-resizing
* Basic vector operations: push, pop, resize, clear, free, etc.
* Optional methods: contains, sort, sort_reversed, print, print_indent

---

## 🔧 Getting Started

### 1. **Include the header**

```c
#include "vec.h"
```

### 2. **Define a vector type**

To create a dynamic array of `int`, do:

```c
vec_define(int, ints, int_vec);
```

This creates a vector type called `ints` with functions prefixed with `int_vec`.

---

## 🚀 Usage Example

```c
#include <stdio.h>
#include "vec.h"

typedef struct Person {
    char name[50];
    int age;
} Person;

vec_define(Person, People);
vec_define_free_simple(Person, People);

int main() {
    People people;
    people_init(&people);  // Initialize the vector

    // Add elements
    Person p1 = {"Alice", 30};
    Person p2 = {"Bob", 25};
    Person p3 = {"Charlie", 35};

    people_push(&people, p1);
    people_push(&people, p2);
    people_push(&people, p3);

    // Print elements
    people_print(people);

    // Access an element
    Person p = people_at(people, 1);
    printf("Element at index 1: { name: \"%s\", age: %d }\n", p.name, p.age);

    // Modify an element
    Person updated = {"Bob Jr.", 26};
    people_set(&people, 1, updated);
    printf("Modified element at index 1: { name: \"%s\", age: %d }\n",
           people_at(people, 1).name, people_at(people, 1).age);

    // Remove last element
    Person popped = people_pop(&people);
    printf("Popped: { name: \"%s\", age: %d }\n", popped.name, popped.age);

    // Clean up
    people_clear(people);
    return 0;
}
```

---

## 🧪 Output

```c
Element at index 1: { name: "Bob", age: 25 }
Modified element at index 1: { name: "Bob Jr.", age: 26 }
Popped: { name: "Charlie", age: 35 }
```

## 🔍 Example with Primitive Types

```c
#include <stdio.h>
#include "vec.h"

// Creates a vector of integers named `ints`
vec_define_primitive(int);

int main() {
    ints v;
    ints_init(&v);

    ints_push(&v, 10);
    ints_push(&v, 30);
    ints_push(&v, 20);
    ints_push(&v, 50);
    ints_push(&v, 5);

    printf("Popped %d\n", ints_pop(&v));

    ints_print(v);
    printf("\n");

    // Sort the vector
    ints_sort(&v);

    // Reverse the vector
    ints_reverse(&v);

    // Clean up
    ints_clear(&v);
    return 0;
}
```

## 🛠️ Technical Overview of All Functions

Below is a full list of available default vector functions. These are generated using:

```c
vec_define(type, NAME)
```

Or use `vec_define2` to specify the function suffix:

```c
vec_define2(type, my_vec, NAME) // vector's type is my_vec and functions start with NAME
```

Once defined, you can call functions like `NAME_init`, `NAME_push`, etc.

---

### 🔧 Initialization & Allocation

| Function                           | Description                                   | Example                       |
| ---------------------------------- | --------------------------------------------- | ----------------------------- |
| `NAME_alloc()`                     | Allocates a vector on the heap.               | `NAME *v = NAME_alloc();`     |
| `NAME_init(&v)`                    | Initializes vector with default capacity (4). | `NAME_init(&v);`              |
| `NAME_init_reserved(&v, capacity)` | Initializes vector with specific capacity.    | `NAME_init_reserved(&v, 16);` |

---

### 📦 Data Manipulation

| Function                     | Description                                   | Example                     |
| ---------------------------- | --------------------------------------------- | --------------------------- |
| `NAME_push(&v, value)`       | Adds an element to the end.                   | `NAME_push(&v, 42);`        |
| `NAME_pop(&v)`               | Removes and returns the last element.         | `int x = NAME_pop(&v);`     |
| `NAME_back(v)`               | Gets a pointer to the last element.           | `int *last = NAME_back(v);` |
| `NAME_at(v, index)`          | Gets a value at an index (with bounds check). | `int x = NAME_at(v, 2);`    |
| `NAME_set(&v, index, value)` | Sets the value at a given index.              | `NAME_set(&v, 1, 99);`      |

---

### 🧹 Management

| Function                     | Description                                           | Example                              |
| ---------------------------- | ----------------------------------------------------- | ------------------------------------ |
| `NAME_empty(v)`              | Checks if vector is empty. Returns 1 or 0.            | `if (NAME_empty(v)) { /* empty */ }` |
| `NAME_reverse(&v)`           | Reverses the vector.                                  | `NAME_reverse(&v);`                  |
| `NAME_shrink(&v)`            | Shrinks capacity to match size. (saves memory)        | `NAME_shrink(&v);`                   |
| `NAME_reserve(&v, capacity)` | Ensures vector can hold at least `capacity` elements. | `NAME_reserve(&v, 100);`             |
| `NAME_realloc(&v, capacity)` | Reallocates to a new capacity (not recommended).      | `NAME_realloc(&v, 50);`              |

---

### 🧩 Defining optional methods

Here's a quick overview of optional methods you can define for your vector type:

| Defined with          | Function                                   | Description                                               | Example                                     |
| --------------------- | ------------------------------------------ | --------------------------------------------------------- | ------------------------------------------- |
| `vec_define_contains` | `NAME_contains(v, value)`                  | Checks if the vector contains a value. Returns 1 or 0.    | `if (NAME_contains(v, 42)) { /* found */ }` |
| `vec_define_sort`     | `NAME_sort(&v)`                            | Sorts the vector in place.                                | `NAME_sort(&v);`                            |
| `vec_define_sort`     | `NAME_sort_reversed(&v)`                   | Sorts the vector in place (in reverse).                   | `NAME_sort_reversed(&v);`                   |
| `vec_define_print`    | `NAME_print(v)`                            | Prints the vector elements.                               | `NAME_print(v);`                            |
| `vec_define_print`    | `NAME_print_indent(v, indent)`             | Prints the vector elements with the given indentation.    | `NAME_print_indent(v, 6);`                  |
| `vec_define_free`     | `NAME_resize(&v, new_size, default_value)` | Resizes the vector, filling new slots with default value. | `NAME_resize(&v, 10, default_value);`       |
| `vec_define_free`     | `NAME_clear(&v)`                           | Frees every element and sets the size to 0.               | `NAME_clear(&v);`                           |

Here are the macros to define these optional methods:

```c
vec_define_contains(type, vector_type, boolean_expression);
vec_define_sort(type, vector_type, comparison_expression);
vec_define_print(type, vector_type, printing_statement);
vec_define_free(type, vector_type, free_statement);

// OR if you want to specify the function prefix (by default function_prefix=vector_type)

vec_define_contains2(type, vector_type, function_prefix, boolean_expression);
vec_define_sort2(type, vector_type, function_prefix, comparison_expression);
vec_define_print2(type, vector_type, function_prefix, printing_statement, newline); // if given true for newline, every element will be in a new line
vec_define_free2(type, vector_type, function_prefix, free_statement);

```

Here are the examples for defining these optional methods:

```c
vec_define_contains(int, ints, a == b);
vec_define_sort(int, ints, a > b);
vec_define_print(int, ints, printf("%d", a));
vec_define_free(int, ints,); // Third argument is for freeing an element, it's an int so no need to. (Variable `a` is defined that is the element, free(a.some_prop) for example)

// And here's how you can specify the function prefix:

vec_define_contains2(int, ints, int_vec, a == b);
vec_define_sort2(int, ints, int_vec, a > b);
vec_define_print2(int, ints, int_vec, printf("%d", a), false); // last argument tells it to not put a newline
vec_define_free2(int, ints, int_vec,);
```

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](./LICENSE) file for details.

---

## 💬 Feedback & Contributions

Found a bug? Have an improvement idea? Feel free to open an issue or submit a pull request.

---

📁 **Looking for the previous version?**
The legacy implementation has been preserved in [`README_legacy.md`](./README_legacy.md) and
[`vec_legacy.h`](./vec_legacy.h) for reference.
